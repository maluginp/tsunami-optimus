/********************************************************************************
** Form generated from reading UI file 'dialogaddmeasure.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDMEASURE_H
#define UI_DIALOGADDMEASURE_H

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

class Ui_DialogAddMeasure
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lnName;
    QLabel *label_2;
    QComboBox *boxType;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancel;
    QPushButton *btnAdd;

    void setupUi(QDialog *DialogAddMeasure)
    {
        if (DialogAddMeasure->objectName().isEmpty())
            DialogAddMeasure->setObjectName(QString::fromUtf8("DialogAddMeasure"));
        DialogAddMeasure->resize(284, 112);
        gridLayout = new QGridLayout(DialogAddMeasure);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(DialogAddMeasure);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        lnName = new QLineEdit(DialogAddMeasure);
        lnName->setObjectName(QString::fromUtf8("lnName"));

        gridLayout->addWidget(lnName, 0, 2, 1, 2);

        label_2 = new QLabel(DialogAddMeasure);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        boxType = new QComboBox(DialogAddMeasure);
        boxType->setObjectName(QString::fromUtf8("boxType"));

        gridLayout->addWidget(boxType, 1, 2, 1, 2);

        horizontalSpacer = new QSpacerItem(59, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        btnCancel = new QPushButton(DialogAddMeasure);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        gridLayout->addWidget(btnCancel, 2, 1, 1, 2);

        btnAdd = new QPushButton(DialogAddMeasure);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        gridLayout->addWidget(btnAdd, 2, 3, 1, 1);


        retranslateUi(DialogAddMeasure);
        QObject::connect(btnAdd, SIGNAL(clicked()), DialogAddMeasure, SLOT(accept()));
        QObject::connect(btnCancel, SIGNAL(clicked()), DialogAddMeasure, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAddMeasure);
    } // setupUi

    void retranslateUi(QDialog *DialogAddMeasure)
    {
        DialogAddMeasure->setWindowTitle(QApplication::translate("DialogAddMeasure", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogAddMeasure", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogAddMeasure", "\320\242\320\270\320\277:", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("DialogAddMeasure", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("DialogAddMeasure", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogAddMeasure: public Ui_DialogAddMeasure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDMEASURE_H
