/********************************************************************************
** Form generated from reading UI file 'formweightconst.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMWEIGHTCONST_H
#define UI_FORMWEIGHTCONST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_FormWeightConst
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *plotter;
    QTableView *weightsTableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;
    QPushButton *saveButton;

    void setupUi(QDialog *FormWeightConst)
    {
        if (FormWeightConst->objectName().isEmpty())
            FormWeightConst->setObjectName(QString::fromUtf8("FormWeightConst"));
        FormWeightConst->resize(854, 552);
        gridLayout = new QGridLayout(FormWeightConst);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        plotter = new QCustomPlot(FormWeightConst);
        plotter->setObjectName(QString::fromUtf8("plotter"));
        plotter->setMinimumSize(QSize(500, 300));
        plotter->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(plotter);

        weightsTableView = new QTableView(FormWeightConst);
        weightsTableView->setObjectName(QString::fromUtf8("weightsTableView"));
        weightsTableView->setMinimumSize(QSize(300, 0));
        weightsTableView->setMaximumSize(QSize(400, 16777215));
        weightsTableView->verticalHeader()->setVisible(false);

        horizontalLayout_2->addWidget(weightsTableView);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QPushButton(FormWeightConst);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);

        saveButton = new QPushButton(FormWeightConst);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout->addWidget(saveButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(FormWeightConst);

        QMetaObject::connectSlotsByName(FormWeightConst);
    } // setupUi

    void retranslateUi(QDialog *FormWeightConst)
    {
        FormWeightConst->setWindowTitle(QApplication::translate("FormWeightConst", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\262\320\265\321\201\320\276\320\262\321\213\321\205 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("FormWeightConst", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("FormWeightConst", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormWeightConst: public Ui_FormWeightConst {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMWEIGHTCONST_H
