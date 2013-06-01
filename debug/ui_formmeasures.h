/********************************************************************************
** Form generated from reading UI file 'formmeasures.ui'
**
** Created: Sun 2. Jun 00:25:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMEASURES_H
#define UI_FORMMEASURES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormMeasures
{
public:
    QAction *action;
    QAction *action_2;
    QAction *actionAddSet;
    QAction *actionAddMeasure;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lnTypesFilter;
    QListView *listDataset;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnAddSet;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lnMeasuresFIlter;
    QListView *listMeasures;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAddMeasure;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_4;
    QTableView *tblInfo;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnEditMeasure;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnAccept;
    QMenuBar *menubar;
    QMenu *menu_2;
    QMenu *menu_4;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FormMeasures)
    {
        if (FormMeasures->objectName().isEmpty())
            FormMeasures->setObjectName(QString::fromUtf8("FormMeasures"));
        FormMeasures->resize(823, 573);
        action = new QAction(FormMeasures);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(FormMeasures);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        actionAddSet = new QAction(FormMeasures);
        actionAddSet->setObjectName(QString::fromUtf8("actionAddSet"));
        actionAddMeasure = new QAction(FormMeasures);
        actionAddMeasure->setObjectName(QString::fromUtf8("actionAddMeasure"));
        centralwidget = new QWidget(FormMeasures);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setContentsMargins(6, 6, 6, 6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lnTypesFilter = new QLineEdit(groupBox);
        lnTypesFilter->setObjectName(QString::fromUtf8("lnTypesFilter"));

        verticalLayout->addWidget(lnTypesFilter);

        listDataset = new QListView(groupBox);
        listDataset->setObjectName(QString::fromUtf8("listDataset"));
        listDataset->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listDataset->setTabKeyNavigation(false);
        listDataset->setDefaultDropAction(Qt::MoveAction);
        listDataset->setSelectionMode(QAbstractItemView::SingleSelection);
        listDataset->setMovement(QListView::Static);
        listDataset->setFlow(QListView::TopToBottom);
        listDataset->setProperty("isWrapping", QVariant(false));
        listDataset->setLayoutMode(QListView::SinglePass);
        listDataset->setViewMode(QListView::ListMode);
        listDataset->setUniformItemSizes(false);
        listDataset->setWordWrap(false);
        listDataset->setSelectionRectVisible(false);

        verticalLayout->addWidget(listDataset);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        btnAddSet = new QPushButton(groupBox);
        btnAddSet->setObjectName(QString::fromUtf8("btnAddSet"));

        horizontalLayout_4->addWidget(btnAddSet);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setContentsMargins(6, 6, 6, 6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lnMeasuresFIlter = new QLineEdit(groupBox_2);
        lnMeasuresFIlter->setObjectName(QString::fromUtf8("lnMeasuresFIlter"));

        verticalLayout_3->addWidget(lnMeasuresFIlter);

        listMeasures = new QListView(groupBox_2);
        listMeasures->setObjectName(QString::fromUtf8("listMeasures"));
        listMeasures->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(listMeasures);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnAddMeasure = new QPushButton(groupBox_2);
        btnAddMeasure->setObjectName(QString::fromUtf8("btnAddMeasure"));

        horizontalLayout_2->addWidget(btnAddMeasure);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setContentsMargins(6, 6, 6, 6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tblInfo = new QTableView(groupBox_3);
        tblInfo->setObjectName(QString::fromUtf8("tblInfo"));
        tblInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblInfo->setTabKeyNavigation(false);
        tblInfo->setProperty("showDropIndicator", QVariant(false));
        tblInfo->horizontalHeader()->setVisible(false);
        tblInfo->horizontalHeader()->setStretchLastSection(true);
        tblInfo->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(tblInfo);


        gridLayout_4->addLayout(verticalLayout_4, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btnEditMeasure = new QPushButton(groupBox_3);
        btnEditMeasure->setObjectName(QString::fromUtf8("btnEditMeasure"));

        horizontalLayout_3->addWidget(btnEditMeasure);


        gridLayout_4->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        btnAccept = new QPushButton(centralwidget);
        btnAccept->setObjectName(QString::fromUtf8("btnAccept"));

        horizontalLayout_5->addWidget(btnAccept);


        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        FormMeasures->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FormMeasures);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 823, 25));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_4 = new QMenu(menu_2);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        FormMeasures->setMenuBar(menubar);
        statusbar = new QStatusBar(FormMeasures);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FormMeasures->setStatusBar(statusbar);

        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu_2->addAction(menu_4->menuAction());
        menu_4->addAction(actionAddSet);
        menu_4->addAction(actionAddMeasure);

        retranslateUi(FormMeasures);

        QMetaObject::connectSlotsByName(FormMeasures);
    } // setupUi

    void retranslateUi(QMainWindow *FormMeasures)
    {
        FormMeasures->setWindowTitle(QApplication::translate("FormMeasures", "\320\235\320\260\320\261\320\276\321\200 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\271", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("FormMeasures", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\260\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("FormMeasures", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        actionAddSet->setText(QApplication::translate("FormMeasures", "\320\235\320\260\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        actionAddMeasure->setText(QApplication::translate("FormMeasures", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FormMeasures", "\320\235\320\260\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        lnTypesFilter->setText(QString());
        lnTypesFilter->setPlaceholderText(QApplication::translate("FormMeasures", "\320\235\320\260\320\261\320\265\321\200\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\275\320\260\320\261\320\276\321\200\320\260", 0, QApplication::UnicodeUTF8));
        btnAddSet->setText(QApplication::translate("FormMeasures", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\260\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FormMeasures", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        lnMeasuresFIlter->setText(QString());
        lnMeasuresFIlter->setPlaceholderText(QApplication::translate("FormMeasures", "\320\235\320\260\320\261\320\265\321\200\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        btnAddMeasure->setText(QApplication::translate("FormMeasures", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FormMeasures", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        btnEditMeasure->setText(QApplication::translate("FormMeasures", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        btnAccept->setText(QApplication::translate("FormMeasures", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\275\320\260\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("FormMeasures", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("FormMeasures", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("FormMeasures", "\320\237\321\200\320\260\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormMeasures: public Ui_FormMeasures {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMEASURES_H
