/********************************************************************************
** Form generated from reading UI file 'dialogaddconstant.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDCONSTANT_H
#define UI_DIALOGADDCONSTANT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogAddConstant
{
public:
    QGridLayout *gridLayout;
    QLabel *const1Label;
    QLineEdit *const1LineEdit;
    QLabel *const2Label;
    QLineEdit *const2LineEdit;
    QPushButton *addButton;

    void setupUi(QDialog *DialogAddConstant)
    {
        if (DialogAddConstant->objectName().isEmpty())
            DialogAddConstant->setObjectName(QString::fromUtf8("DialogAddConstant"));
        DialogAddConstant->resize(204, 169);
        gridLayout = new QGridLayout(DialogAddConstant);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        const1Label = new QLabel(DialogAddConstant);
        const1Label->setObjectName(QString::fromUtf8("const1Label"));

        gridLayout->addWidget(const1Label, 0, 0, 1, 1);

        const1LineEdit = new QLineEdit(DialogAddConstant);
        const1LineEdit->setObjectName(QString::fromUtf8("const1LineEdit"));

        gridLayout->addWidget(const1LineEdit, 0, 1, 1, 1);

        const2Label = new QLabel(DialogAddConstant);
        const2Label->setObjectName(QString::fromUtf8("const2Label"));

        gridLayout->addWidget(const2Label, 1, 0, 1, 1);

        const2LineEdit = new QLineEdit(DialogAddConstant);
        const2LineEdit->setObjectName(QString::fromUtf8("const2LineEdit"));

        gridLayout->addWidget(const2LineEdit, 1, 1, 1, 1);

        addButton = new QPushButton(DialogAddConstant);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 2, 1, 1, 1);


        retranslateUi(DialogAddConstant);

        QMetaObject::connectSlotsByName(DialogAddConstant);
    } // setupUi

    void retranslateUi(QDialog *DialogAddConstant)
    {
        DialogAddConstant->setWindowTitle(QApplication::translate("DialogAddConstant", "Dialog", 0, QApplication::UnicodeUTF8));
        const1Label->setText(QApplication::translate("DialogAddConstant", "Const1", 0, QApplication::UnicodeUTF8));
        const2Label->setText(QApplication::translate("DialogAddConstant", "Const2", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("DialogAddConstant", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogAddConstant: public Ui_DialogAddConstant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDCONSTANT_H
