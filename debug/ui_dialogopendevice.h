/********************************************************************************
** Form generated from reading UI file 'dialogopendevice.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOPENDEVICE_H
#define UI_DIALOGOPENDEVICE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogOpenDevice
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lnMeasuresFIlter;
    QListView *listDevices;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QTableView *tblInfo;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnAccept;

    void setupUi(QDialog *DialogOpenDevice)
    {
        if (DialogOpenDevice->objectName().isEmpty())
            DialogOpenDevice->setObjectName(QString::fromUtf8("DialogOpenDevice"));
        DialogOpenDevice->resize(575, 529);
        gridLayout = new QGridLayout(DialogOpenDevice);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(DialogOpenDevice);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lnMeasuresFIlter = new QLineEdit(groupBox_2);
        lnMeasuresFIlter->setObjectName(QString::fromUtf8("lnMeasuresFIlter"));

        verticalLayout_3->addWidget(lnMeasuresFIlter);

        listDevices = new QListView(groupBox_2);
        listDevices->setObjectName(QString::fromUtf8("listDevices"));
        listDevices->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(listDevices);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(DialogOpenDevice);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tblInfo = new QTableView(groupBox_3);
        tblInfo->setObjectName(QString::fromUtf8("tblInfo"));
        tblInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblInfo->setTabKeyNavigation(false);
        tblInfo->setProperty("showDropIndicator", QVariant(false));
        tblInfo->horizontalHeader()->setVisible(false);
        tblInfo->horizontalHeader()->setDefaultSectionSize(100);
        tblInfo->horizontalHeader()->setStretchLastSection(true);
        tblInfo->verticalHeader()->setVisible(false);
        tblInfo->verticalHeader()->setCascadingSectionResizes(true);
        tblInfo->verticalHeader()->setDefaultSectionSize(30);

        verticalLayout_4->addWidget(tblInfo);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnAdd = new QPushButton(DialogOpenDevice);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        horizontalLayout_2->addWidget(btnAdd);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnAccept = new QPushButton(DialogOpenDevice);
        btnAccept->setObjectName(QString::fromUtf8("btnAccept"));

        horizontalLayout->addWidget(btnAccept);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        QWidget::setTabOrder(lnMeasuresFIlter, listDevices);
        QWidget::setTabOrder(listDevices, tblInfo);
        QWidget::setTabOrder(tblInfo, btnAccept);
        QWidget::setTabOrder(btnAccept, btnAdd);

        retranslateUi(DialogOpenDevice);

        QMetaObject::connectSlotsByName(DialogOpenDevice);
    } // setupUi

    void retranslateUi(QDialog *DialogOpenDevice)
    {
        DialogOpenDevice->setWindowTitle(QApplication::translate("DialogOpenDevice", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DialogOpenDevice", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260", 0, QApplication::UnicodeUTF8));
        lnMeasuresFIlter->setText(QString());
        lnMeasuresFIlter->setPlaceholderText(QApplication::translate("DialogOpenDevice", "\320\235\320\260\320\261\320\265\321\200\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\276\320\264\320\265\320\273\320\270", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("DialogOpenDevice", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("DialogOpenDevice", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnAccept->setText(QApplication::translate("DialogOpenDevice", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogOpenDevice: public Ui_DialogOpenDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOPENDEVICE_H
