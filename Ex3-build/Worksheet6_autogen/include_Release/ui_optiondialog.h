/********************************************************************************
** Form generated from reading UI file 'optiondialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONDIALOG_H
#define UI_OPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OptionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QCheckBox *checkVisible;
    QLabel *labelR;
    QSpinBox *spinR;
    QLabel *labelG;
    QSpinBox *spinG;
    QLabel *labelB;
    QSpinBox *spinB;
    QCheckBox *checkShrink;
    QCheckBox *checkClip;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionDialog)
    {
        if (OptionDialog->objectName().isEmpty())
            OptionDialog->setObjectName("OptionDialog");
        OptionDialog->resize(400, 320);
        verticalLayout = new QVBoxLayout(OptionDialog);
        verticalLayout->setObjectName("verticalLayout");
        labelName = new QLabel(OptionDialog);
        labelName->setObjectName("labelName");

        verticalLayout->addWidget(labelName);

        lineEditName = new QLineEdit(OptionDialog);
        lineEditName->setObjectName("lineEditName");

        verticalLayout->addWidget(lineEditName);

        checkVisible = new QCheckBox(OptionDialog);
        checkVisible->setObjectName("checkVisible");

        verticalLayout->addWidget(checkVisible);

        labelR = new QLabel(OptionDialog);
        labelR->setObjectName("labelR");

        verticalLayout->addWidget(labelR);

        spinR = new QSpinBox(OptionDialog);
        spinR->setObjectName("spinR");
        spinR->setMaximum(255);

        verticalLayout->addWidget(spinR);

        labelG = new QLabel(OptionDialog);
        labelG->setObjectName("labelG");

        verticalLayout->addWidget(labelG);

        spinG = new QSpinBox(OptionDialog);
        spinG->setObjectName("spinG");
        spinG->setMaximum(255);

        verticalLayout->addWidget(spinG);

        labelB = new QLabel(OptionDialog);
        labelB->setObjectName("labelB");

        verticalLayout->addWidget(labelB);

        spinB = new QSpinBox(OptionDialog);
        spinB->setObjectName("spinB");
        spinB->setMaximum(255);

        verticalLayout->addWidget(spinB);

        checkShrink = new QCheckBox(OptionDialog);
        checkShrink->setObjectName("checkShrink");

        verticalLayout->addWidget(checkShrink);

        checkClip = new QCheckBox(OptionDialog);
        checkClip->setObjectName("checkClip");

        verticalLayout->addWidget(checkClip);

        buttonBox = new QDialogButtonBox(OptionDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(OptionDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, OptionDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, OptionDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(OptionDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionDialog)
    {
        OptionDialog->setWindowTitle(QCoreApplication::translate("OptionDialog", "Item Options", nullptr));
        labelName->setText(QCoreApplication::translate("OptionDialog", "Name", nullptr));
        checkVisible->setText(QCoreApplication::translate("OptionDialog", "Visible", nullptr));
        labelR->setText(QCoreApplication::translate("OptionDialog", "Red", nullptr));
        labelG->setText(QCoreApplication::translate("OptionDialog", "Green", nullptr));
        labelB->setText(QCoreApplication::translate("OptionDialog", "Blue", nullptr));
        checkShrink->setText(QCoreApplication::translate("OptionDialog", "Shrink Filter", nullptr));
        checkClip->setText(QCoreApplication::translate("OptionDialog", "Clip Filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionDialog: public Ui_OptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
