/********************************************************************************
** Form generated from reading UI file 'formstrategy.ui'
**
** Created: Sun 2. Jun 00:25:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSTRATEGY_H
#define UI_FORMSTRATEGY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
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

class Ui_FormStrategy
{
public:
    QAction *actionNewStrategy;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lnModelsFIlter;
    QListView *listStrategies;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *labelDataset;
    QTableView *tblMeasures;
    QCheckBox *weightsCheckBox;
    QGroupBox *descriptionGroupBox;
    QGridLayout *gridLayout_3;
    QTableView *descriptionTableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *setWeightsButton;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FormStrategy)
    {
        if (FormStrategy->objectName().isEmpty())
            FormStrategy->setObjectName(QString::fromUtf8("FormStrategy"));
        FormStrategy->resize(850, 510);
        actionNewStrategy = new QAction(FormStrategy);
        actionNewStrategy->setObjectName(QString::fromUtf8("actionNewStrategy"));
        centralwidget = new QWidget(FormStrategy);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(300, 16777215));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        lnModelsFIlter = new QLineEdit(groupBox_2);
        lnModelsFIlter->setObjectName(QString::fromUtf8("lnModelsFIlter"));

        verticalLayout_3->addWidget(lnModelsFIlter);

        listStrategies = new QListView(groupBox_2);
        listStrategies->setObjectName(QString::fromUtf8("listStrategies"));
        listStrategies->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_3->addWidget(listStrategies);


        gridLayout_6->addLayout(verticalLayout_3, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        labelDataset = new QLabel(groupBox_3);
        labelDataset->setObjectName(QString::fromUtf8("labelDataset"));

        horizontalLayout->addWidget(labelDataset);


        verticalLayout_2->addLayout(horizontalLayout);

        tblMeasures = new QTableView(groupBox_3);
        tblMeasures->setObjectName(QString::fromUtf8("tblMeasures"));
        tblMeasures->horizontalHeader()->setVisible(false);
        tblMeasures->horizontalHeader()->setStretchLastSection(true);
        tblMeasures->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tblMeasures);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        weightsCheckBox = new QCheckBox(groupBox_3);
        weightsCheckBox->setObjectName(QString::fromUtf8("weightsCheckBox"));

        gridLayout_2->addWidget(weightsCheckBox, 1, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox_3);

        descriptionGroupBox = new QGroupBox(centralwidget);
        descriptionGroupBox->setObjectName(QString::fromUtf8("descriptionGroupBox"));
        gridLayout_3 = new QGridLayout(descriptionGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        descriptionTableView = new QTableView(descriptionGroupBox);
        descriptionTableView->setObjectName(QString::fromUtf8("descriptionTableView"));
        descriptionTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        descriptionTableView->setSelectionMode(QAbstractItemView::NoSelection);
        descriptionTableView->horizontalHeader()->setVisible(false);
        descriptionTableView->horizontalHeader()->setHighlightSections(false);
        descriptionTableView->horizontalHeader()->setStretchLastSection(true);
        descriptionTableView->verticalHeader()->setVisible(false);
        descriptionTableView->verticalHeader()->setHighlightSections(false);
        descriptionTableView->verticalHeader()->setStretchLastSection(false);

        gridLayout_3->addWidget(descriptionTableView, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        setWeightsButton = new QPushButton(descriptionGroupBox);
        setWeightsButton->setObjectName(QString::fromUtf8("setWeightsButton"));

        horizontalLayout_2->addWidget(setWeightsButton);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        horizontalLayout_4->addWidget(descriptionGroupBox);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        acceptButton = new QPushButton(centralwidget);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        horizontalLayout_3->addWidget(acceptButton);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        FormStrategy->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FormStrategy);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 850, 25));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        FormStrategy->setMenuBar(menubar);
        statusbar = new QStatusBar(FormStrategy);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FormStrategy->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionNewStrategy);

        retranslateUi(FormStrategy);

        QMetaObject::connectSlotsByName(FormStrategy);
    } // setupUi

    void retranslateUi(QMainWindow *FormStrategy)
    {
        FormStrategy->setWindowTitle(QApplication::translate("FormStrategy", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\201\321\202\321\200\320\260\321\202\320\265\320\263\320\270\320\271", 0, QApplication::UnicodeUTF8));
        actionNewStrategy->setText(QApplication::translate("FormStrategy", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FormStrategy", "\320\241\321\202\321\200\320\260\321\202\320\265\320\263\320\270\320\270", 0, QApplication::UnicodeUTF8));
        lnModelsFIlter->setText(QString());
        lnModelsFIlter->setPlaceholderText(QApplication::translate("FormStrategy", "\320\235\320\260\320\261\320\265\321\200\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\201\321\202\321\200\320\260\321\202\320\265\320\263\320\270\320\270", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FormStrategy", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormStrategy", "\320\235\320\260\320\261\320\276\321\200:", 0, QApplication::UnicodeUTF8));
        labelDataset->setText(QApplication::translate("FormStrategy", "<html><head/><body><p><span style=\" font-style:italic;\">\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\201\321\202\321\200\320\260\321\202\320\265\320\263\320\270\321\216</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        weightsCheckBox->setText(QApplication::translate("FormStrategy", "\320\243\321\207\320\270\321\202\321\213\320\262\320\260\321\202\321\214 \320\262\320\265\321\201\320\276\320\262\321\213\320\265 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        descriptionGroupBox->setTitle(QApplication::translate("FormStrategy", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        setWeightsButton->setText(QApplication::translate("FormStrategy", "\320\227\320\260\320\264\320\260\321\202\321\214 \320\262\320\265\321\201\320\276\320\262\321\213\320\265 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        acceptButton->setText(QApplication::translate("FormStrategy", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("FormStrategy", "\320\241\321\202\321\200\320\260\321\202\320\265\320\263\320\270\321\217", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormStrategy: public Ui_FormStrategy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSTRATEGY_H
