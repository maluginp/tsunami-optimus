/********************************************************************************
** Form generated from reading UI file 'formgraphics.ui'
**
** Created: Sun 2. Jun 00:25:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMGRAPHICS_H
#define UI_FORMGRAPHICS_H

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
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormGraphics
{
public:
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QListView *listGraphics;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *btnAccept;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FormGraphics)
    {
        if (FormGraphics->objectName().isEmpty())
            FormGraphics->setObjectName(QString::fromUtf8("FormGraphics"));
        FormGraphics->resize(640, 495);
        action_3 = new QAction(FormGraphics);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(FormGraphics);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_5 = new QAction(FormGraphics);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_6 = new QAction(FormGraphics);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        centralwidget = new QWidget(FormGraphics);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 241, 401));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 30, 211, 351));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        listGraphics = new QListView(widget);
        listGraphics->setObjectName(QString::fromUtf8("listGraphics"));

        verticalLayout->addWidget(listGraphics);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(260, 10, 371, 401));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 2)
            tableWidget->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem10);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 30, 351, 311));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setStretchLastSection(false);
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(300, 350, 61, 32));
        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(240, 350, 61, 32));
        btnAccept = new QPushButton(centralwidget);
        btnAccept->setObjectName(QString::fromUtf8("btnAccept"));
        btnAccept->setGeometry(QRect(520, 420, 114, 32));
        FormGraphics->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FormGraphics);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 22));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menu);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        FormGraphics->setMenuBar(menubar);
        statusbar = new QStatusBar(FormGraphics);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FormGraphics->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(menu_2->menuAction());
        menu->addAction(action_3);
        menu_2->addAction(action_4);
        menu_2->addAction(action_5);
        menu_3->addAction(action_6);

        retranslateUi(FormGraphics);

        QMetaObject::connectSlotsByName(FormGraphics);
    } // setupUi

    void retranslateUi(QMainWindow *FormGraphics)
    {
        FormGraphics->setWindowTitle(QApplication::translate("FormGraphics", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("FormGraphics", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("FormGraphics", "\320\235\320\260\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        action_5->setText(QApplication::translate("FormGraphics", "\320\223\321\200\320\260\321\204\320\270\320\272", 0, QApplication::UnicodeUTF8));
        action_6->setText(QApplication::translate("FormGraphics", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FormGraphics", "\320\235\320\260\320\261\320\276\321\200\321\213 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262", 0, QApplication::UnicodeUTF8));
        lineEdit->setInputMask(QString());
        lineEdit->setPlaceholderText(QApplication::translate("FormGraphics", "\320\235\320\260\320\261\320\265\321\200\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\275\320\260\320\261\320\276\321\200\320\260", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FormGraphics", "\320\223\321\200\320\260\321\204\320\270\320\272\320\270", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FormGraphics", "\320\236\321\201\321\214 X", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FormGraphics", "\320\236\321\201\321\214 Y", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FormGraphics", "\320\232\320\276\320\275\321\201\321\202\320\260\320\275\321\202\320\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("FormGraphics", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("FormGraphics", "2", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("FormGraphics", "Ub", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 1);
        ___qtablewidgetitem6->setText(QApplication::translate("FormGraphics", "Ib", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 2);
        ___qtablewidgetitem7->setText(QApplication::translate("FormGraphics", "Uc", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(1, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("FormGraphics", "Uc", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(1, 1);
        ___qtablewidgetitem9->setText(QApplication::translate("FormGraphics", "Ic", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(1, 2);
        ___qtablewidgetitem10->setText(QApplication::translate("FormGraphics", "Ib", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_4->setText(QApplication::translate("FormGraphics", "+", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("FormGraphics", "-", 0, QApplication::UnicodeUTF8));
        btnAccept->setText(QApplication::translate("FormGraphics", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("FormGraphics", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("FormGraphics", "\320\235\320\276\320\262\321\213\320\271", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("FormGraphics", "\320\237\321\200\320\260\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormGraphics: public Ui_FormGraphics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMGRAPHICS_H
