/********************************************************************************
** Form generated from reading UI file 'deviceworkspace.ui'
**
** Created: Sun 2. Jun 00:25:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEWORKSPACE_H
#define UI_DEVICEWORKSPACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceWorkspace
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionQuit;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QAction *actionSettings;
    QAction *action_11;
    QAction *action_13;
    QAction *action_14;
    QAction *action_15;
    QAction *actionNewDevice;
    QAction *actionRemoveDevices;
    QWidget *centralWidget;
    QLabel *deviceImage;
    QPushButton *btnExtraction;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelPolarity;
    QLabel *polarityTitleLabel;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelModel;
    QToolButton *btnSetModel;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelDataset;
    QToolButton *btnSetMeasures;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelStrategy;
    QToolButton *btnSetStrategy;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelParameters;
    QToolButton *btnSetParameters;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_3;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DeviceWorkspace)
    {
        if (DeviceWorkspace->objectName().isEmpty())
            DeviceWorkspace->setObjectName(QString::fromUtf8("DeviceWorkspace"));
        DeviceWorkspace->resize(629, 471);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DeviceWorkspace->sizePolicy().hasHeightForWidth());
        DeviceWorkspace->setSizePolicy(sizePolicy);
        DeviceWorkspace->setMinimumSize(QSize(629, 471));
        DeviceWorkspace->setMaximumSize(QSize(629, 471));
        actionOpen = new QAction(DeviceWorkspace);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionClose = new QAction(DeviceWorkspace);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionQuit = new QAction(DeviceWorkspace);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        action_5 = new QAction(DeviceWorkspace);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_6 = new QAction(DeviceWorkspace);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        action_7 = new QAction(DeviceWorkspace);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        action_8 = new QAction(DeviceWorkspace);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        actionSettings = new QAction(DeviceWorkspace);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        action_11 = new QAction(DeviceWorkspace);
        action_11->setObjectName(QString::fromUtf8("action_11"));
        action_13 = new QAction(DeviceWorkspace);
        action_13->setObjectName(QString::fromUtf8("action_13"));
        action_14 = new QAction(DeviceWorkspace);
        action_14->setObjectName(QString::fromUtf8("action_14"));
        action_15 = new QAction(DeviceWorkspace);
        action_15->setObjectName(QString::fromUtf8("action_15"));
        actionNewDevice = new QAction(DeviceWorkspace);
        actionNewDevice->setObjectName(QString::fromUtf8("actionNewDevice"));
        actionRemoveDevices = new QAction(DeviceWorkspace);
        actionRemoveDevices->setObjectName(QString::fromUtf8("actionRemoveDevices"));
        centralWidget = new QWidget(DeviceWorkspace);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        deviceImage = new QLabel(centralWidget);
        deviceImage->setObjectName(QString::fromUtf8("deviceImage"));
        deviceImage->setGeometry(QRect(270, 60, 321, 341));
        deviceImage->setAutoFillBackground(false);
        deviceImage->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        deviceImage->setPixmap(QPixmap(QString::fromUtf8(":/images/images/bjt.png")));
        deviceImage->setScaledContents(false);
        deviceImage->setAlignment(Qt::AlignCenter);
        btnExtraction = new QPushButton(centralWidget);
        btnExtraction->setObjectName(QString::fromUtf8("btnExtraction"));
        btnExtraction->setGeometry(QRect(50, 320, 131, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        btnExtraction->setFont(font);
        layoutWidget_4 = new QWidget(centralWidget);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(380, 10, 233, 30));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        labelPolarity = new QLabel(layoutWidget_4);
        labelPolarity->setObjectName(QString::fromUtf8("labelPolarity"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        labelPolarity->setFont(font1);

        horizontalLayout_10->addWidget(labelPolarity);

        polarityTitleLabel = new QLabel(layoutWidget_4);
        polarityTitleLabel->setObjectName(QString::fromUtf8("polarityTitleLabel"));

        horizontalLayout_10->addWidget(polarityTitleLabel);

        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 61, 222, 241));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_11->setFont(font2);

        verticalLayout_5->addWidget(label_11);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelModel = new QLabel(layoutWidget);
        labelModel->setObjectName(QString::fromUtf8("labelModel"));
        labelModel->setFont(font);

        horizontalLayout_6->addWidget(labelModel);

        btnSetModel = new QToolButton(layoutWidget);
        btnSetModel->setObjectName(QString::fromUtf8("btnSetModel"));
        btnSetModel->setFont(font);

        horizontalLayout_6->addWidget(btnSetModel);


        verticalLayout_5->addLayout(horizontalLayout_6);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font2);

        verticalLayout_6->addWidget(label_13);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labelDataset = new QLabel(layoutWidget);
        labelDataset->setObjectName(QString::fromUtf8("labelDataset"));
        labelDataset->setFont(font);

        horizontalLayout_7->addWidget(labelDataset);

        btnSetMeasures = new QToolButton(layoutWidget);
        btnSetMeasures->setObjectName(QString::fromUtf8("btnSetMeasures"));
        btnSetMeasures->setFont(font);

        horizontalLayout_7->addWidget(btnSetMeasures);


        verticalLayout_6->addLayout(horizontalLayout_7);


        gridLayout->addLayout(verticalLayout_6, 1, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font2);

        verticalLayout_8->addWidget(label_17);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        labelStrategy = new QLabel(layoutWidget);
        labelStrategy->setObjectName(QString::fromUtf8("labelStrategy"));
        labelStrategy->setFont(font);

        horizontalLayout_9->addWidget(labelStrategy);

        btnSetStrategy = new QToolButton(layoutWidget);
        btnSetStrategy->setObjectName(QString::fromUtf8("btnSetStrategy"));
        btnSetStrategy->setFont(font);

        horizontalLayout_9->addWidget(btnSetStrategy);


        verticalLayout_8->addLayout(horizontalLayout_9);


        gridLayout->addLayout(verticalLayout_8, 2, 0, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font2);

        verticalLayout_7->addWidget(label_15);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labelParameters = new QLabel(layoutWidget);
        labelParameters->setObjectName(QString::fromUtf8("labelParameters"));
        labelParameters->setFont(font);

        horizontalLayout_8->addWidget(labelParameters);

        btnSetParameters = new QToolButton(layoutWidget);
        btnSetParameters->setObjectName(QString::fromUtf8("btnSetParameters"));
        btnSetParameters->setFont(font);

        horizontalLayout_8->addWidget(btnSetParameters);


        verticalLayout_7->addLayout(horizontalLayout_8);


        gridLayout->addLayout(verticalLayout_7, 3, 0, 1, 1);

        DeviceWorkspace->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DeviceWorkspace);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 629, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_3 = new QMenu(menu);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        DeviceWorkspace->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DeviceWorkspace);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DeviceWorkspace->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DeviceWorkspace);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DeviceWorkspace->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(menu_3->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionClose);
        menu->addAction(actionRemoveDevices);
        menu->addAction(actionQuit);
        menu_3->addAction(actionNewDevice);
        menu_3->addAction(action_11);
        menu_3->addAction(action_13);
        menu_3->addAction(action_14);
        menu_3->addAction(action_15);
        menu_2->addAction(actionSettings);

        retranslateUi(DeviceWorkspace);

        QMetaObject::connectSlotsByName(DeviceWorkspace);
    } // setupUi

    void retranslateUi(QMainWindow *DeviceWorkspace)
    {
        DeviceWorkspace->setWindowTitle(QApplication::translate("DeviceWorkspace", "\320\240\320\260\320\261\320\276\321\207\320\260\321\217 \320\276\320\261\320\273\320\260\321\201\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("DeviceWorkspace", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("DeviceWorkspace", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("DeviceWorkspace", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actionClose->setShortcut(QApplication::translate("DeviceWorkspace", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("DeviceWorkspace", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("DeviceWorkspace", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_5->setText(QApplication::translate("DeviceWorkspace", "\320\234\320\276\320\264\320\265\320\273\320\265\320\271", 0, QApplication::UnicodeUTF8));
        action_6->setText(QApplication::translate("DeviceWorkspace", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        action_7->setText(QApplication::translate("DeviceWorkspace", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\271", 0, QApplication::UnicodeUTF8));
        action_8->setText(QApplication::translate("DeviceWorkspace", "\320\223\321\200\320\260\321\204\320\270\320\272\320\276\320\262", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("DeviceWorkspace", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
        action_11->setText(QApplication::translate("DeviceWorkspace", "\320\234\320\276\320\264\320\265\320\273\321\214", 0, QApplication::UnicodeUTF8));
        action_13->setText(QApplication::translate("DeviceWorkspace", "\320\235\320\260\320\261\320\276\321\200 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        action_14->setText(QApplication::translate("DeviceWorkspace", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        action_15->setText(QApplication::translate("DeviceWorkspace", "\320\235\320\260\320\261\320\276\321\200 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262", 0, QApplication::UnicodeUTF8));
        actionNewDevice->setText(QApplication::translate("DeviceWorkspace", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", 0, QApplication::UnicodeUTF8));
        actionNewDevice->setShortcut(QApplication::translate("DeviceWorkspace", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionRemoveDevices->setText(QApplication::translate("DeviceWorkspace", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        deviceImage->setText(QString());
        btnExtraction->setText(QApplication::translate("DeviceWorkspace", "\320\255\320\272\321\201\321\202\321\200\320\260\320\272\321\206\320\270\321\217\n"
"\320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        labelPolarity->setText(QApplication::translate("DeviceWorkspace", "\320\237\320\276\320\273\321\217\321\200\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
        polarityTitleLabel->setText(QString());
        label_11->setText(QApplication::translate("DeviceWorkspace", "\320\234\320\276\320\264\320\265\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        labelModel->setText(QApplication::translate("DeviceWorkspace", "<span style=\" font-style:italic; color:#949494;\">\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276</span>", 0, QApplication::UnicodeUTF8));
        btnSetModel->setText(QApplication::translate("DeviceWorkspace", "...", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("DeviceWorkspace", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        labelDataset->setText(QApplication::translate("DeviceWorkspace", "<html><head/><body><p><span style=\" font-style:italic; color:#949494;\">\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnSetMeasures->setText(QApplication::translate("DeviceWorkspace", "...", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("DeviceWorkspace", "\320\241\321\202\321\200\320\260\321\202\320\265\320\263\320\270\321\217", 0, QApplication::UnicodeUTF8));
        labelStrategy->setText(QApplication::translate("DeviceWorkspace", "<html><head/><body><p><span style=\" font-style:italic; color:#949494;\">\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnSetStrategy->setText(QApplication::translate("DeviceWorkspace", "...", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("DeviceWorkspace", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
        labelParameters->setText(QApplication::translate("DeviceWorkspace", "<html><head/><body><p><span style=\" font-style:italic; color:#949494;\">\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnSetParameters->setText(QApplication::translate("DeviceWorkspace", "...", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("DeviceWorkspace", "\320\237\321\200\320\270\320\261\320\276\321\200", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("DeviceWorkspace", "\320\235\320\276\320\262\321\213\320\271", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("DeviceWorkspace", "\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DeviceWorkspace: public Ui_DeviceWorkspace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEWORKSPACE_H
