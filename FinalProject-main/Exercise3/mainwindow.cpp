#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QStatusBar>
#include <QTreeView>
#include <QVBoxLayout>
#include <QMenu>

#include <vtkOpenVRRenderer.h>
#include <vtkOpenVRRenderWindow.h>
#include <vtkOpenVRRenderWindowInteractor.h>
#include <functional>
#include "C:/OpenVR/headers/openvr.h"

#include "optiondialog.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Icons (safe fix)
    ui->actionOpen->setIcon(QIcon(":/icons/Open.png"));
    ui->actionSave->setIcon(QIcon(":/icons/Save.png"));
    ui->actionExit->setIcon(QIcon(":/icons/Exit.png"));

    vtkWidget = new QVTKOpenGLNativeWidget(ui->vtkPlaceholder);

    QVBoxLayout* layout = new QVBoxLayout(ui->vtkPlaceholder);
    layout->addWidget(vtkWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->vtkPlaceholder->setLayout(layout);

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkWidget->setRenderWindow(renderWindow);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);
    renderer->SetBackground(0.1, 0.2, 0.4);

    partList = new ModelPartList("Parts List");
    ui->treeView->setModel(partList);

    // Context menu (safe feature for marks)
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QTreeView::customContextMenuRequested,
            this, &MainWindow::showContextMenu);

    connect(ui->treeView, &QTreeView::clicked,
            this, &MainWindow::handleTreeClicked);

    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Context menu
void MainWindow::showContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);

    if (!index.isValid())
        return;

    QMenu menu(this);

    QAction *editAction = menu.addAction("Edit Part");
    QAction *removeAction = menu.addAction("Remove Part");

    QAction *selected = menu.exec(ui->treeView->viewport()->mapToGlobal(pos));

    if (selected == editAction)
    {
        ui->treeView->setCurrentIndex(index);
        on_actionItem_Options_triggered();
    }
    else if (selected == removeAction)
    {
        ModelPart* part = static_cast<ModelPart*>(index.internalPointer());

        if (part && part->getActor())
        {
            renderer->RemoveActor(part->getActor());

            // SAFE REMOVE (no model breaking)
            partList->removeRow(index.row(), index.parent());

            updateRender();

            emit statusUpdateMessage("Part removed", 2000);
        }
    }
}

void MainWindow::handleTreeClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    ModelPart* item = static_cast<ModelPart*>(index.internalPointer());

    if (!item)
        return;

    emit statusUpdateMessage(QString("Selected: %1").arg(item->getName()), 2000);
}

void MainWindow::on_Button1_clicked()
{
    on_actionItem_Options_triggered();
}

void MainWindow::on_Button2_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();

    if (!index.isValid()) {
        emit statusUpdateMessage("No item selected", 2000);
        return;
    }

    ModelPart* part = static_cast<ModelPart*>(index.internalPointer());

    if (!part) {
        emit statusUpdateMessage("Invalid selection", 2000);
        return;
    }

    vtkSmartPointer<vtkActor> actor = part->getActor();

    if (actor != nullptr) {
        renderer->RemoveActor(actor);
        vtkWidget->renderWindow()->Render();
        emit statusUpdateMessage(QString("Removed from render: %1").arg(part->getName()), 2000);
    }
    else {
        emit statusUpdateMessage("Selected item has no actor", 2000);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open STL File"),
        "",
        tr("STL Files (*.stl);;All Files (*)")
        );

    if (fileName.isEmpty())
        return;

    QModelIndex index = ui->treeView->currentIndex();

    QFileInfo info(fileName);
    QList<QVariant> data = { info.fileName(), "true", "255,0,89" };

    QModelIndex newIndex = partList->appendChild(index, data);

    ModelPart* newPart = static_cast<ModelPart*>(newIndex.internalPointer());

    if (newPart) {
        newPart->loadSTL(fileName);
        emit statusUpdateMessage(QString("Loaded: %1").arg(info.fileName()), 2000);
    }

    ui->treeView->expandAll();
    updateRender();
}

void MainWindow::on_actionSave_triggered()
{
    QMessageBox::information(this, "Save", "Save is not implemented yet.");
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionItem_Options_triggered()
{
    QModelIndex index = ui->treeView->currentIndex();

    if (!index.isValid()) {
        emit statusUpdateMessage("No item selected", 2000);
        return;
    }

    ModelPart* part = static_cast<ModelPart*>(index.internalPointer());

    if (!part) {
        emit statusUpdateMessage("Invalid selection", 2000);
        return;
    }

    OptionDialog dlg(this);
    dlg.setModelPart(part);

    if (dlg.exec() == QDialog::Accepted) {
        partList->dataChanged(index, index);
        updateRender();
        emit statusUpdateMessage(QString("Updated: %1").arg(part->getName()), 2000);
    }
}

void MainWindow::updateRender()
{
    renderer->RemoveAllViewProps();

    int rows = partList->rowCount(QModelIndex());

    for (int i = 0; i < rows; ++i) {
        updateRenderFromTree(partList->index(i, 0, QModelIndex()));
    }

    renderer->ResetCamera();
    renderer->Render();
    vtkWidget->renderWindow()->Render();
}

void MainWindow::updateRenderFromTree(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    if (selectedPart && selectedPart->visible()) {
        vtkSmartPointer<vtkActor> actor = selectedPart->getActor();

        if (actor != nullptr) {
            renderer->AddActor(actor);
        }
    }

    int rows = partList->rowCount(index);

    for (int i = 0; i < rows; ++i) {
        updateRenderFromTree(partList->index(i, 0, index));
    }
}

void MainWindow::on_ButtonVR_clicked()
{
    vtkSmartPointer<vtkOpenVRRenderer> vrRenderer =
        vtkSmartPointer<vtkOpenVRRenderer>::New();

    vtkSmartPointer<vtkOpenVRRenderWindow> vrWindow =
        vtkSmartPointer<vtkOpenVRRenderWindow>::New();

    vtkSmartPointer<vtkOpenVRRenderWindowInteractor> vrInteractor =
        vtkSmartPointer<vtkOpenVRRenderWindowInteractor>::New();

    vrWindow->AddRenderer(vrRenderer);
    vrInteractor->SetRenderWindow(vrWindow);

    vrRenderer->SetBackground(0.1, 0.1, 0.2);

    int topRows = partList->rowCount(QModelIndex());
    for (int i = 0; i < topRows; ++i)
    {
        QModelIndex index = partList->index(i, 0, QModelIndex());
        ModelPart* part = static_cast<ModelPart*>(index.internalPointer());

        if (part && part->visible() && part->getActor())
        {
            vtkSmartPointer<vtkActor> copiedActor =
                vtkSmartPointer<vtkActor>::New();

            copiedActor->ShallowCopy(part->getActor());
            vrRenderer->AddActor(copiedActor);
        }
    }

    vrRenderer->ResetCamera();

    vrWindow->Render();
    vrInteractor->Start();
}
