/********************************************************************************
** Form generated from reading UI file 'editormeasures.ui'
**
** Created: Sun 2. Jun 02:32:51 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORMEASURES_H
#define UI_EDITORMEASURES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorMeasures
{
public:
    QAction *action_2;
    QAction *actionImport;
    QAction *actionExport;
    QAction *action_5;
    QAction *actionAddColumn;
    QAction *actionAddRow;
    QAction *actionCopyToClipboard;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QTabWidget *tabGraphics;
    QWidget *tab;
    QWidget *tab_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QTableView *tblMeasures;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAddRow;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableView *tblInfo;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSave;
    QPushButton *btnClose;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnDelConst;
    QPushButton *btnAddConst;
    QSpacerItem *horizontalSpacer_3;
    QTableView *tblConstants;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditorMeasures)
    {
        if (EditorMeasures->objectName().isEmpty())
            EditorMeasures->setObjectName(QString::fromUtf8("EditorMeasures"));
        EditorMeasures->resize(938, 748);
        action_2 = new QAction(EditorMeasures);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        actionImport = new QAction(EditorMeasures);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        actionExport = new QAction(EditorMeasures);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        action_5 = new QAction(EditorMeasures);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        actionAddColumn = new QAction(EditorMeasures);
        actionAddColumn->setObjectName(QString::fromUtf8("actionAddColumn"));
        actionAddRow = new QAction(EditorMeasures);
        actionAddRow->setObjectName(QString::fromUtf8("actionAddRow"));
        actionCopyToClipboard = new QAction(EditorMeasures);
        actionCopyToClipboard->setObjectName(QString::fromUtf8("actionCopyToClipboard"));
        centralwidget = new QWidget(EditorMeasures);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabGraphics = new QTabWidget(centralwidget);
        tabGraphics->setObjectName(QString::fromUtf8("tabGraphics"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabGraphics->sizePolicy().hasHeightForWidth());
        tabGraphics->setSizePolicy(sizePolicy1);
        tabGraphics->setMinimumSize(QSize(100, 350));
        tabGraphics->setMaximumSize(QSize(350, 350));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabGraphics->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabGraphics->addTab(tab_2, QString());

        gridLayout_4->addWidget(tabGraphics, 1, 2, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tblMeasures = new QTableView(groupBox_3);
        tblMeasures->setObjectName(QString::fromUtf8("tblMeasures"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tblMeasures->sizePolicy().hasHeightForWidth());
        tblMeasures->setSizePolicy(sizePolicy2);
        tblMeasures->setMinimumSize(QSize(300, 0));
        tblMeasures->verticalHeader()->setVisible(false);
        tblMeasures->verticalHeader()->setHighlightSections(false);

        gridLayout->addWidget(tblMeasures, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnRefresh = new QPushButton(groupBox_3);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));

        horizontalLayout_2->addWidget(btnRefresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnAddRow = new QPushButton(groupBox_3);
        btnAddRow->setObjectName(QString::fromUtf8("btnAddRow"));

        horizontalLayout_2->addWidget(btnAddRow);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 0, 1, 3, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setMinimumSize(QSize(0, 250));
        groupBox->setMaximumSize(QSize(350, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tblInfo = new QTableView(groupBox);
        tblInfo->setObjectName(QString::fromUtf8("tblInfo"));
        tblInfo->setMaximumSize(QSize(350, 16777215));
        tblInfo->horizontalHeader()->setStretchLastSection(true);
        tblInfo->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tblInfo, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnSave->sizePolicy().hasHeightForWidth());
        btnSave->setSizePolicy(sizePolicy4);
        btnSave->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(btnSave);

        btnClose = new QPushButton(centralwidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setEnabled(true);
        sizePolicy4.setHeightForWidth(btnClose->sizePolicy().hasHeightForWidth());
        btnClose->setSizePolicy(sizePolicy4);
        btnClose->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(btnClose);


        gridLayout_4->addLayout(horizontalLayout, 2, 2, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        groupBox_2->setMinimumSize(QSize(300, 0));
        groupBox_2->setMaximumSize(QSize(600, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btnDelConst = new QPushButton(groupBox_2);
        btnDelConst->setObjectName(QString::fromUtf8("btnDelConst"));
        btnDelConst->setMinimumSize(QSize(40, 0));
        btnDelConst->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(btnDelConst);

        btnAddConst = new QPushButton(groupBox_2);
        btnAddConst->setObjectName(QString::fromUtf8("btnAddConst"));
        sizePolicy4.setHeightForWidth(btnAddConst->sizePolicy().hasHeightForWidth());
        btnAddConst->setSizePolicy(sizePolicy4);
        btnAddConst->setMinimumSize(QSize(40, 0));
        btnAddConst->setMaximumSize(QSize(40, 16777215));
        btnAddConst->setBaseSize(QSize(30, 0));

        horizontalLayout_3->addWidget(btnAddConst);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        tblConstants = new QTableView(groupBox_2);
        tblConstants->setObjectName(QString::fromUtf8("tblConstants"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(tblConstants->sizePolicy().hasHeightForWidth());
        tblConstants->setSizePolicy(sizePolicy5);
        tblConstants->setMinimumSize(QSize(200, 0));
        tblConstants->horizontalHeader()->setVisible(false);
        tblConstants->horizontalHeader()->setStretchLastSection(true);
        tblConstants->verticalHeader()->setVisible(false);
        tblConstants->verticalHeader()->setStretchLastSection(false);

        gridLayout_3->addWidget(tblConstants, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 3, 1);

        EditorMeasures->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditorMeasures);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 938, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menu);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        EditorMeasures->setMenuBar(menubar);
        statusbar = new QStatusBar(EditorMeasures);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        EditorMeasures->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(menu_2->menuAction());
        menu->addAction(action_2);
        menu->addAction(actionImport);
        menu->addAction(actionExport);
        menu->addAction(action_5);
        menu_2->addAction(actionAddColumn);
        menu_2->addAction(actionAddRow);
        menu_3->addAction(actionCopyToClipboard);

        retranslateUi(EditorMeasures);

        QMetaObject::connectSlotsByName(EditorMeasures);
    } // setupUi

    void retranslateUi(QMainWindow *EditorMeasures)
    {
        EditorMeasures->setWindowTitle(QApplication::translate("EditorMeasures", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\271", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("EditorMeasures", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actionImport->setText(QApplication::translate("EditorMeasures", "\320\230\320\274\320\277\320\276\321\200\321\202", 0, QApplication::UnicodeUTF8));
        actionImport->setShortcut(QApplication::translate("EditorMeasures", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionExport->setText(QApplication::translate("EditorMeasures", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", 0, QApplication::UnicodeUTF8));
        actionExport->setShortcut(QApplication::translate("EditorMeasures", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        action_5->setText(QApplication::translate("EditorMeasures", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        actionAddColumn->setText(QApplication::translate("EditorMeasures", "\320\232\320\276\320\273\320\276\320\275\320\272\321\203", 0, QApplication::UnicodeUTF8));
        actionAddRow->setText(QApplication::translate("EditorMeasures", "\320\241\321\202\321\200\320\276\320\272\321\203", 0, QApplication::UnicodeUTF8));
        actionCopyToClipboard->setText(QApplication::translate("EditorMeasures", "\320\241\320\272\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\262 \320\261\321\203\321\204\320\265\321\200", 0, QApplication::UnicodeUTF8));
        actionCopyToClipboard->setShortcut(QApplication::translate("EditorMeasures", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        tabGraphics->setTabText(tabGraphics->indexOf(tab), QApplication::translate("EditorMeasures", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabGraphics->setTabText(tabGraphics->indexOf(tab_2), QApplication::translate("EditorMeasures", "Tab 2", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("EditorMeasures", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        btnRefresh->setText(QApplication::translate("EditorMeasures", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnAddRow->setText(QApplication::translate("EditorMeasures", "+", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("EditorMeasures", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("EditorMeasures", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("EditorMeasures", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("EditorMeasures", "\320\232\320\276\320\275\321\201\321\202\320\260\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        btnDelConst->setText(QApplication::translate("EditorMeasures", "-", 0, QApplication::UnicodeUTF8));
        btnAddConst->setText(QApplication::translate("EditorMeasures", "+", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("EditorMeasures", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("EditorMeasures", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("EditorMeasures", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditorMeasures: public Ui_EditorMeasures {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORMEASURES_H
