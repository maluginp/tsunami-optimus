/********************************************************************************
** Form generated from reading UI file 'formminimisation.ui'
**
** Created: Sun 2. Jun 00:25:38 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMINIMISATION_H
#define UI_FORMMINIMISATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormMinimisation
{
public:
    QAction *actionCopyToClipboard;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTabWidget *tabGraphics;
    QWidget *tab;
    QWidget *tab_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSavePlot;
    QTextBrowser *logger;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *labelStatus;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QLabel *labelIterations;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLabel *labelError;
    QTableView *tblParameters;
    QPushButton *btnSaveParameters;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressMinimisation;
    QPushButton *btnOperation;
    QPushButton *btnStop;
    QPushButton *pushButton_2;

    void setupUi(QDialog *FormMinimisation)
    {
        if (FormMinimisation->objectName().isEmpty())
            FormMinimisation->setObjectName(QString::fromUtf8("FormMinimisation"));
        FormMinimisation->resize(852, 567);
        actionCopyToClipboard = new QAction(FormMinimisation);
        actionCopyToClipboard->setObjectName(QString::fromUtf8("actionCopyToClipboard"));
        gridLayout_2 = new QGridLayout(FormMinimisation);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabGraphics = new QTabWidget(FormMinimisation);
        tabGraphics->setObjectName(QString::fromUtf8("tabGraphics"));
        tabGraphics->setMinimumSize(QSize(0, 300));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabGraphics->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabGraphics->addTab(tab_2, QString());

        gridLayout->addWidget(tabGraphics, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        btnSavePlot = new QPushButton(FormMinimisation);
        btnSavePlot->setObjectName(QString::fromUtf8("btnSavePlot"));

        gridLayout->addWidget(btnSavePlot, 1, 1, 1, 1);

        logger = new QTextBrowser(FormMinimisation);
        logger->setObjectName(QString::fromUtf8("logger"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logger->sizePolicy().hasHeightForWidth());
        logger->setSizePolicy(sizePolicy);
        logger->setMinimumSize(QSize(0, 0));
        logger->setMaximumSize(QSize(16777215, 250));

        gridLayout->addWidget(logger, 2, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 6, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_11 = new QLabel(FormMinimisation);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_4->addWidget(label_11);

        labelStatus = new QLabel(FormMinimisation);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setMinimumSize(QSize(100, 0));

        horizontalLayout_4->addWidget(labelStatus);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_9 = new QLabel(FormMinimisation);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_2->addWidget(label_9);

        labelIterations = new QLabel(FormMinimisation);
        labelIterations->setObjectName(QString::fromUtf8("labelIterations"));

        horizontalLayout_2->addWidget(labelIterations);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        label_7 = new QLabel(FormMinimisation);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);

        labelError = new QLabel(FormMinimisation);
        labelError->setObjectName(QString::fromUtf8("labelError"));

        horizontalLayout->addWidget(labelError);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 1);

        tblParameters = new QTableView(FormMinimisation);
        tblParameters->setObjectName(QString::fromUtf8("tblParameters"));

        gridLayout_2->addWidget(tblParameters, 2, 1, 1, 2);

        btnSaveParameters = new QPushButton(FormMinimisation);
        btnSaveParameters->setObjectName(QString::fromUtf8("btnSaveParameters"));

        gridLayout_2->addWidget(btnSaveParameters, 3, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        progressMinimisation = new QProgressBar(FormMinimisation);
        progressMinimisation->setObjectName(QString::fromUtf8("progressMinimisation"));
        progressMinimisation->setValue(24);
        progressMinimisation->setTextVisible(false);
        progressMinimisation->setInvertedAppearance(false);

        horizontalLayout_3->addWidget(progressMinimisation);

        btnOperation = new QPushButton(FormMinimisation);
        btnOperation->setObjectName(QString::fromUtf8("btnOperation"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnOperation->sizePolicy().hasHeightForWidth());
        btnOperation->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(btnOperation);

        btnStop = new QPushButton(FormMinimisation);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        horizontalLayout_3->addWidget(btnStop);


        gridLayout_2->addLayout(horizontalLayout_3, 4, 1, 1, 2);

        pushButton_2 = new QPushButton(FormMinimisation);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 5, 2, 1, 1);

        btnSaveParameters->raise();
        tblParameters->raise();
        pushButton_2->raise();

        retranslateUi(FormMinimisation);
        QObject::connect(pushButton_2, SIGNAL(clicked()), FormMinimisation, SLOT(accept()));

        tabGraphics->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormMinimisation);
    } // setupUi

    void retranslateUi(QDialog *FormMinimisation)
    {
        FormMinimisation->setWindowTitle(QApplication::translate("FormMinimisation", "\320\255\320\272\321\201\321\202\321\200\320\260\320\272\321\206\320\270\321\217 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        actionCopyToClipboard->setText(QApplication::translate("FormMinimisation", "\320\241\320\272\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actionCopyToClipboard->setShortcut(QApplication::translate("FormMinimisation", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        tabGraphics->setTabText(tabGraphics->indexOf(tab), QApplication::translate("FormMinimisation", "Ib-Ub", 0, QApplication::UnicodeUTF8));
        tabGraphics->setTabText(tabGraphics->indexOf(tab_2), QApplication::translate("FormMinimisation", "Ic-Uc", 0, QApplication::UnicodeUTF8));
        btnSavePlot->setText(QApplication::translate("FormMinimisation", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", 0, QApplication::UnicodeUTF8));
        logger->setHtml(QApplication::translate("FormMinimisation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff325d;\">\320\235\320\260\321\207\320\260\320\273\321\214\320\275\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">BF=1, AR=10</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff842d;\">\320\230\321\202\320\265\321\200\320\260\321\206\320\270\321\217 #1</span><"
                        "/p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\250\320\260\320\263=100</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff1210;\">\320\236\321\210\320\270\320\261\320\272\320\260: </span>\320\235\320\265\321\205\320\262\320\260\321\202\320\260\320\265\321\202 \320\264\320\260\320\275\320\275\321\213\321\205</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#c0a22a;\">\320\237\321\200\320\265\320\264\321\203\320\277\321\200\320\265\320\266\320\264\320\265\320\275\320\270\320\265:</span><span style=\" color:#ffeb39;\"> </span>\320\275\320\265\321\205\320\262\320\260\321\202\320\260\320\265\321\202 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\260</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margi"
                        "n-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff325d;\">\320\236\320\277\321\202\320\270\320\274\320\260\320\273\321\214\320\275\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#000000;\">BF=0.5, AR=1</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("FormMinimisation", "\320\241\321\202\320\260\321\202\321\203\321\201:", 0, QApplication::UnicodeUTF8));
        labelStatus->setText(QApplication::translate("FormMinimisation", "\320\240\320\260\320\261\320\276\321\202\320\260\320\265\321\202", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FormMinimisation", "\320\230\321\202\320\265\321\200\320\260\321\206\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        labelIterations->setText(QApplication::translate("FormMinimisation", "1/30", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FormMinimisation", "\320\236\321\210\320\270\320\261\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        labelError->setText(QApplication::translate("FormMinimisation", "0.011", 0, QApplication::UnicodeUTF8));
        btnSaveParameters->setText(QApplication::translate("FormMinimisation", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnOperation->setText(QApplication::translate("FormMinimisation", "\320\227\320\260\320\277\321\203\321\201\320\272", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("FormMinimisation", "\320\241\321\202\320\276\320\277", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("FormMinimisation", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormMinimisation: public Ui_FormMinimisation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMINIMISATION_H
