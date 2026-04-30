/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionItem_Options;
    QWidget *rightpanel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QWidget *vtkPlaceholder;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *ButtonVR;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Open.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionOpen->setIcon(icon);
        actionOpen->setVisible(true);
        actionOpen->setMenuRole(QAction::MenuRole::NoRole);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave->setIcon(icon1);
        actionSave->setMenuRole(QAction::MenuRole::NoRole);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/Exit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionExit->setIcon(icon2);
        actionExit->setMenuRole(QAction::MenuRole::NoRole);
        actionItem_Options = new QAction(MainWindow);
        actionItem_Options->setObjectName("actionItem_Options");
        actionItem_Options->setMenuRole(QAction::MenuRole::NoRole);
        rightpanel = new QWidget(MainWindow);
        rightpanel->setObjectName("rightpanel");
        verticalLayout = new QVBoxLayout(rightpanel);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        treeView = new QTreeView(rightpanel);
        treeView->setObjectName("treeView");
        treeView->setMinimumSize(QSize(250, 0));
        treeView->setMaximumSize(QSize(300, 16777215));
        treeView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);

        horizontalLayout->addWidget(treeView);

        vtkPlaceholder = new QWidget(rightpanel);
        vtkPlaceholder->setObjectName("vtkPlaceholder");
        vtkPlaceholder->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vtkPlaceholder->sizePolicy().hasHeightForWidth());
        vtkPlaceholder->setSizePolicy(sizePolicy);
        vtkPlaceholder->setMinimumSize(QSize(400, 400));

        horizontalLayout->addWidget(vtkPlaceholder);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Button1 = new QPushButton(rightpanel);
        Button1->setObjectName("Button1");

        horizontalLayout_2->addWidget(Button1);

        Button2 = new QPushButton(rightpanel);
        Button2->setObjectName("Button2");

        horizontalLayout_2->addWidget(Button2);

        ButtonVR = new QPushButton(rightpanel);
        ButtonVR->setObjectName("ButtonVR");

        horizontalLayout_2->addWidget(ButtonVR);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(rightpanel);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setIconSize(QSize(30, 30));
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "exit", nullptr));
        actionItem_Options->setText(QCoreApplication::translate("MainWindow", "Item Options", nullptr));
        Button1->setText(QCoreApplication::translate("MainWindow", " Load STL", nullptr));
        Button2->setText(QCoreApplication::translate("MainWindow", "Load Folder", nullptr));
        ButtonVR->setText(QCoreApplication::translate("MainWindow", "Start VR", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        mainToolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
