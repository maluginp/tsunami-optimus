/********************************************************************************
** Form generated from reading UI file 'dialogdeletedevices.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDELETEDEVICES_H
#define UI_DIALOGDELETEDEVICES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DialogDeleteDevices
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QListView *devicesListView;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QListView *removesListView;
    QPushButton *toRemoveButton;
    QPushButton *fromRemoveButton;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *removeButton;

    void setupUi(QDialog *DialogDeleteDevices)
    {
        if (DialogDeleteDevices->objectName().isEmpty())
            DialogDeleteDevices->setObjectName(QString::fromUtf8("DialogDeleteDevices"));
        DialogDeleteDevices->resize(571, 433);
        gridLayout_3 = new QGridLayout(DialogDeleteDevices);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(DialogDeleteDevices);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        devicesListView = new QListView(groupBox);
        devicesListView->setObjectName(QString::fromUtf8("devicesListView"));
        devicesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        devicesListView->setSelectionMode(QAbstractItemView::MultiSelection);

        gridLayout->addWidget(devicesListView, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 4, 1);

        verticalSpacer = new QSpacerItem(20, 140, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(DialogDeleteDevices);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        removesListView = new QListView(groupBox_2);
        removesListView->setObjectName(QString::fromUtf8("removesListView"));
        removesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        removesListView->setSelectionMode(QAbstractItemView::MultiSelection);

        gridLayout_2->addWidget(removesListView, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 2, 4, 2);

        toRemoveButton = new QPushButton(DialogDeleteDevices);
        toRemoveButton->setObjectName(QString::fromUtf8("toRemoveButton"));

        gridLayout_3->addWidget(toRemoveButton, 1, 1, 1, 1);

        fromRemoveButton = new QPushButton(DialogDeleteDevices);
        fromRemoveButton->setObjectName(QString::fromUtf8("fromRemoveButton"));

        gridLayout_3->addWidget(fromRemoveButton, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 139, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(247, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 4, 0, 1, 1);

        cancelButton = new QPushButton(DialogDeleteDevices);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout_3->addWidget(cancelButton, 4, 2, 1, 1);

        removeButton = new QPushButton(DialogDeleteDevices);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        gridLayout_3->addWidget(removeButton, 4, 3, 1, 1);


        retranslateUi(DialogDeleteDevices);

        QMetaObject::connectSlotsByName(DialogDeleteDevices);
    } // setupUi

    void retranslateUi(QDialog *DialogDeleteDevices)
    {
        DialogDeleteDevices->setWindowTitle(QApplication::translate("DialogDeleteDevices", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DialogDeleteDevices", "\320\237\321\200\320\270\320\261\320\276\321\200\321\213", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DialogDeleteDevices", "\320\235\320\260 \321\203\320\264\320\260\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        toRemoveButton->setText(QApplication::translate("DialogDeleteDevices", ">>", 0, QApplication::UnicodeUTF8));
        fromRemoveButton->setText(QApplication::translate("DialogDeleteDevices", "<<", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DialogDeleteDevices", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("DialogDeleteDevices", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogDeleteDevices: public Ui_DialogDeleteDevices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDELETEDEVICES_H
