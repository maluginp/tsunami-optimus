/********************************************************************************
** Form generated from reading UI file 'formparameters.ui'
**
** Created: Sun 2. Jun 00:25:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMPARAMETERS_H
#define UI_FORMPARAMETERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormParameters
{
public:
    QAction *actionAddSet;
    QAction *action_3;
    QAction *actionSaveTemplate;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *boxParameterSets;
    QPushButton *btnAddSet;
    QPushButton *btnCancel;
    QPushButton *btnAccept;
    QPushButton *btnRemove;
    QSpacerItem *horizontalSpacer;
    QTableView *tblParameters;
    QPushButton *btnAdd;
    QMenuBar *menubar;
    QMenu *menu_2;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FormParameters)
    {
        if (FormParameters->objectName().isEmpty())
            FormParameters->setObjectName(QString::fromUtf8("FormParameters"));
        FormParameters->resize(697, 537);
        actionAddSet = new QAction(FormParameters);
        actionAddSet->setObjectName(QString::fromUtf8("actionAddSet"));
        action_3 = new QAction(FormParameters);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        actionSaveTemplate = new QAction(FormParameters);
        actionSaveTemplate->setObjectName(QString::fromUtf8("actionSaveTemplate"));
        centralwidget = new QWidget(FormParameters);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        boxParameterSets = new QComboBox(centralwidget);
        boxParameterSets->setObjectName(QString::fromUtf8("boxParameterSets"));

        horizontalLayout->addWidget(boxParameterSets);

        btnAddSet = new QPushButton(centralwidget);
        btnAddSet->setObjectName(QString::fromUtf8("btnAddSet"));

        horizontalLayout->addWidget(btnAddSet);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        btnCancel = new QPushButton(centralwidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        gridLayout->addWidget(btnCancel, 2, 3, 1, 1);

        btnAccept = new QPushButton(centralwidget);
        btnAccept->setObjectName(QString::fromUtf8("btnAccept"));

        gridLayout->addWidget(btnAccept, 2, 4, 1, 1);

        btnRemove = new QPushButton(centralwidget);
        btnRemove->setObjectName(QString::fromUtf8("btnRemove"));

        gridLayout->addWidget(btnRemove, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(199, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        tblParameters = new QTableView(centralwidget);
        tblParameters->setObjectName(QString::fromUtf8("tblParameters"));
        tblParameters->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tblParameters, 1, 0, 1, 5);

        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        gridLayout->addWidget(btnAdd, 2, 1, 1, 1);

        FormParameters->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FormParameters);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 697, 25));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu = new QMenu(menu_2);
        menu->setObjectName(QString::fromUtf8("menu"));
        FormParameters->setMenuBar(menubar);
        statusbar = new QStatusBar(FormParameters);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FormParameters->setStatusBar(statusbar);

        menubar->addAction(menu_2->menuAction());
        menu_2->addAction(menu->menuAction());
        menu_2->addAction(actionSaveTemplate);
        menu->addAction(actionAddSet);
        menu->addAction(action_3);

        retranslateUi(FormParameters);

        QMetaObject::connectSlotsByName(FormParameters);
    } // setupUi

    void retranslateUi(QMainWindow *FormParameters)
    {
        FormParameters->setWindowTitle(QApplication::translate("FormParameters", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        actionAddSet->setText(QApplication::translate("FormParameters", "\320\235\320\260\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("FormParameters", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200", 0, QApplication::UnicodeUTF8));
        actionSaveTemplate->setText(QApplication::translate("FormParameters", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272 \321\210\320\260\320\261\320\273\320\276\320\275", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormParameters", "\320\235\320\260\320\261\320\276\321\200:", 0, QApplication::UnicodeUTF8));
        boxParameterSets->clear();
        boxParameterSets->insertItems(0, QStringList()
         << QApplication::translate("FormParameters", "vostok_1", 0, QApplication::UnicodeUTF8)
        );
        btnAddSet->setText(QApplication::translate("FormParameters", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("FormParameters", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnAccept->setText(QApplication::translate("FormParameters", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnRemove->setText(QApplication::translate("FormParameters", "-", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("FormParameters", "+", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("FormParameters", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("FormParameters", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormParameters: public Ui_FormParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMPARAMETERS_H
