/********************************************************************************
** Form generated from reading UI file 'viewerplot.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWERPLOT_H
#define UI_VIEWERPLOT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_ViewerPlot
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *plotter;

    void setupUi(QWidget *ViewerPlot)
    {
        if (ViewerPlot->objectName().isEmpty())
            ViewerPlot->setObjectName(QString::fromUtf8("ViewerPlot"));
        ViewerPlot->resize(640, 480);
        gridLayout = new QGridLayout(ViewerPlot);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plotter = new QCustomPlot(ViewerPlot);
        plotter->setObjectName(QString::fromUtf8("plotter"));

        gridLayout->addWidget(plotter, 0, 0, 1, 1);


        retranslateUi(ViewerPlot);

        QMetaObject::connectSlotsByName(ViewerPlot);
    } // setupUi

    void retranslateUi(QWidget *ViewerPlot)
    {
        ViewerPlot->setWindowTitle(QApplication::translate("ViewerPlot", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ViewerPlot: public Ui_ViewerPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWERPLOT_H
