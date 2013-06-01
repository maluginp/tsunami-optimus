/********************************************************************************
** Form generated from reading UI file 'dialognewdevice.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGNEWDEVICE_H
#define UI_DIALOGNEWDEVICE_H

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

class Ui_DialogNewDevice
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lnName;
    QLabel *labelType;
    QComboBox *boxType;
    QLabel *labelPolarity;
    QComboBox *boxPolarity;
    QLabel *labelGround;
    QComboBox *boxGround;
    QLabel *widthChannelLabel;
    QLineEdit *widthChannelLineEdit;
    QLabel *lengthChannelLabel;
    QLineEdit *lengthChannelLineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;

    void setupUi(QDialog *DialogNewDevice)
    {
        if (DialogNewDevice->objectName().isEmpty())
            DialogNewDevice->setObjectName(QString::fromUtf8("DialogNewDevice"));
        DialogNewDevice->resize(323, 254);
        gridLayout = new QGridLayout(DialogNewDevice);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(DialogNewDevice);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lnName = new QLineEdit(DialogNewDevice);
        lnName->setObjectName(QString::fromUtf8("lnName"));

        gridLayout->addWidget(lnName, 0, 1, 1, 1);

        labelType = new QLabel(DialogNewDevice);
        labelType->setObjectName(QString::fromUtf8("labelType"));

        gridLayout->addWidget(labelType, 1, 0, 1, 1);

        boxType = new QComboBox(DialogNewDevice);
        boxType->setObjectName(QString::fromUtf8("boxType"));

        gridLayout->addWidget(boxType, 1, 1, 1, 1);

        labelPolarity = new QLabel(DialogNewDevice);
        labelPolarity->setObjectName(QString::fromUtf8("labelPolarity"));

        gridLayout->addWidget(labelPolarity, 2, 0, 1, 1);

        boxPolarity = new QComboBox(DialogNewDevice);
        boxPolarity->setObjectName(QString::fromUtf8("boxPolarity"));

        gridLayout->addWidget(boxPolarity, 2, 1, 1, 1);

        labelGround = new QLabel(DialogNewDevice);
        labelGround->setObjectName(QString::fromUtf8("labelGround"));

        gridLayout->addWidget(labelGround, 3, 0, 1, 1);

        boxGround = new QComboBox(DialogNewDevice);
        boxGround->setObjectName(QString::fromUtf8("boxGround"));

        gridLayout->addWidget(boxGround, 3, 1, 1, 1);

        widthChannelLabel = new QLabel(DialogNewDevice);
        widthChannelLabel->setObjectName(QString::fromUtf8("widthChannelLabel"));

        gridLayout->addWidget(widthChannelLabel, 4, 0, 1, 1);

        widthChannelLineEdit = new QLineEdit(DialogNewDevice);
        widthChannelLineEdit->setObjectName(QString::fromUtf8("widthChannelLineEdit"));

        gridLayout->addWidget(widthChannelLineEdit, 4, 1, 1, 1);

        lengthChannelLabel = new QLabel(DialogNewDevice);
        lengthChannelLabel->setObjectName(QString::fromUtf8("lengthChannelLabel"));

        gridLayout->addWidget(lengthChannelLabel, 5, 0, 1, 1);

        lengthChannelLineEdit = new QLineEdit(DialogNewDevice);
        lengthChannelLineEdit->setObjectName(QString::fromUtf8("lengthChannelLineEdit"));

        gridLayout->addWidget(lengthChannelLineEdit, 5, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 6, 0, 1, 1);

        btnAdd = new QPushButton(DialogNewDevice);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        gridLayout->addWidget(btnAdd, 6, 1, 1, 1);


        retranslateUi(DialogNewDevice);

        QMetaObject::connectSlotsByName(DialogNewDevice);
    } // setupUi

    void retranslateUi(QDialog *DialogNewDevice)
    {
        DialogNewDevice->setWindowTitle(QApplication::translate("DialogNewDevice", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogNewDevice", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        labelType->setText(QApplication::translate("DialogNewDevice", "\320\242\320\270\320\277:", 0, QApplication::UnicodeUTF8));
        labelPolarity->setText(QApplication::translate("DialogNewDevice", "\320\237\320\276\320\273\321\217\321\200\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
        labelGround->setText(QApplication::translate("DialogNewDevice", "\320\227\320\265\320\274\320\273\321\217:", 0, QApplication::UnicodeUTF8));
        widthChannelLabel->setText(QApplication::translate("DialogNewDevice", "\320\250\320\270\321\200\320\270\320\275\320\260:", 0, QApplication::UnicodeUTF8));
        lengthChannelLabel->setText(QApplication::translate("DialogNewDevice", "\320\224\320\273\320\270\320\275\320\260:", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("DialogNewDevice", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogNewDevice: public Ui_DialogNewDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGNEWDEVICE_H
