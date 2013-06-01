/********************************************************************************
** Form generated from reading UI file 'formmodels.ui'
**
** Created: Sun 2. Jun 00:25:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMODELS_H
#define UI_FORMMODELS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormModels
{
public:
    QAction *action_2;
    QAction *action_3;
    QWidget *centralwidget;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lnModelsFIlter;
    QListView *listModels;
    QPushButton *btnAccept;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QTableView *tblInfo;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FormModels)
    {
        if (FormModels->objectName().isEmpty())
            FormModels->setObjectName(QString::fromUtf8("FormModels"));
        FormModels->resize(492, 463);
        action_2 = new QAction(FormModels);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(FormModels);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralwidget = new QWidget(FormModels);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 0, 211, 371));
        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 20, 211, 351));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        lnModelsFIlter = new QLineEdit(layoutWidget_2);
        lnModelsFIlter->setObjectName(QString::fromUtf8("lnModelsFIlter"));

        verticalLayout_3->addWidget(lnModelsFIlter);

        listModels = new QListView(layoutWidget_2);
        listModels->setObjectName(QString::fromUtf8("listModels"));
        listModels->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(listModels);

        btnAccept = new QPushButton(centralwidget);
        btnAccept->setObjectName(QString::fromUtf8("btnAccept"));
        btnAccept->setGeometry(QRect(390, 380, 88, 27));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(220, 0, 261, 371));
        layoutWidget_3 = new QWidget(groupBox_3);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 20, 258, 351));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        tblInfo = new QTableView(layoutWidget_3);
        tblInfo->setObjectName(QString::fromUtf8("tblInfo"));
        tblInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblInfo->setProperty("showDropIndicator", QVariant(false));
        tblInfo->horizontalHeader()->setVisible(false);
        tblInfo->horizontalHeader()->setStretchLastSection(true);
        tblInfo->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(tblInfo);

        FormModels->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FormModels);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 492, 25));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menu);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        FormModels->setMenuBar(menubar);
        statusbar = new QStatusBar(FormModels);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FormModels->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(menu_2->menuAction());
        menu->addAction(action_3);
        menu_2->addAction(action_2);

        retranslateUi(FormModels);

        QMetaObject::connectSlotsByName(FormModels);
    } // setupUi

    void retranslateUi(QMainWindow *FormModels)
    {
        FormModels->setWindowTitle(QApplication::translate("FormModels", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\274\320\276\320\264\320\265\320\273\320\265\320\271", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("FormModels", "\320\242\320\270\320\277", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("FormModels", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FormModels", "\320\234\320\276\320\264\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        lnModelsFIlter->setText(QString());
        lnModelsFIlter->setPlaceholderText(QApplication::translate("FormModels", "\320\235\320\260\320\261\320\265\321\200\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\276\320\264\320\265\320\273\320\270", 0, QApplication::UnicodeUTF8));
        btnAccept->setText(QApplication::translate("FormModels", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FormModels", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("FormModels", "\320\234\320\276\320\264\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("FormModels", "\320\235\320\276\320\262\321\213\320\271", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("FormModels", "\320\237\321\200\320\260\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormModels: public Ui_FormModels {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMODELS_H
