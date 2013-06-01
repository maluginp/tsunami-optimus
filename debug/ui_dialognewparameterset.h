/********************************************************************************
** Form generated from reading UI file 'dialognewparameterset.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGNEWPARAMETERSET_H
#define UI_DIALOGNEWPARAMETERSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DialogNewParameterSet
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lnName;
    QLabel *label_2;
    QComboBox *boxTemplates;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;

    void setupUi(QDialog *DialogNewParameterSet)
    {
        if (DialogNewParameterSet->objectName().isEmpty())
            DialogNewParameterSet->setObjectName(QString::fromUtf8("DialogNewParameterSet"));
        DialogNewParameterSet->resize(267, 148);
        gridLayout = new QGridLayout(DialogNewParameterSet);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(DialogNewParameterSet);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lnName = new QLineEdit(DialogNewParameterSet);
        lnName->setObjectName(QString::fromUtf8("lnName"));

        gridLayout->addWidget(lnName, 0, 1, 1, 1);

        label_2 = new QLabel(DialogNewParameterSet);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        boxTemplates = new QComboBox(DialogNewParameterSet);
        boxTemplates->setObjectName(QString::fromUtf8("boxTemplates"));

        gridLayout->addWidget(boxTemplates, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(111, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        btnAdd = new QPushButton(DialogNewParameterSet);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        gridLayout->addWidget(btnAdd, 2, 1, 1, 1);


        retranslateUi(DialogNewParameterSet);

        QMetaObject::connectSlotsByName(DialogNewParameterSet);
    } // setupUi

    void retranslateUi(QDialog *DialogNewParameterSet)
    {
        DialogNewParameterSet->setWindowTitle(QApplication::translate("DialogNewParameterSet", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\260\320\261\320\276\321\200 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogNewParameterSet", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogNewParameterSet", "\320\250\320\260\320\261\320\273\320\276\320\275:", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("DialogNewParameterSet", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogNewParameterSet: public Ui_DialogNewParameterSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGNEWPARAMETERSET_H
