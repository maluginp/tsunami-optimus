/********************************************************************************
** Form generated from reading UI file 'dialogsaveparameters.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSAVEPARAMETERS_H
#define UI_DIALOGSAVEPARAMETERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogSaveParameters
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QLineEdit *parameterSaveAsLineEdit;
    QCheckBox *saveAsCheckBox;
    QLabel *parameterSetLabel;

    void setupUi(QDialog *DialogSaveParameters)
    {
        if (DialogSaveParameters->objectName().isEmpty())
            DialogSaveParameters->setObjectName(QString::fromUtf8("DialogSaveParameters"));
        DialogSaveParameters->resize(254, 155);
        gridLayout = new QGridLayout(DialogSaveParameters);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cancelButton = new QPushButton(DialogSaveParameters);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        saveButton = new QPushButton(DialogSaveParameters);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout->addWidget(saveButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        parameterSaveAsLineEdit = new QLineEdit(DialogSaveParameters);
        parameterSaveAsLineEdit->setObjectName(QString::fromUtf8("parameterSaveAsLineEdit"));

        gridLayout->addWidget(parameterSaveAsLineEdit, 2, 0, 1, 1);

        saveAsCheckBox = new QCheckBox(DialogSaveParameters);
        saveAsCheckBox->setObjectName(QString::fromUtf8("saveAsCheckBox"));

        gridLayout->addWidget(saveAsCheckBox, 1, 0, 1, 1);

        parameterSetLabel = new QLabel(DialogSaveParameters);
        parameterSetLabel->setObjectName(QString::fromUtf8("parameterSetLabel"));
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        parameterSetLabel->setFont(font);

        gridLayout->addWidget(parameterSetLabel, 0, 0, 1, 1);

        QWidget::setTabOrder(saveAsCheckBox, parameterSaveAsLineEdit);
        QWidget::setTabOrder(parameterSaveAsLineEdit, saveButton);
        QWidget::setTabOrder(saveButton, cancelButton);

        retranslateUi(DialogSaveParameters);
        QObject::connect(saveButton, SIGNAL(clicked()), DialogSaveParameters, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DialogSaveParameters, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSaveParameters);
    } // setupUi

    void retranslateUi(QDialog *DialogSaveParameters)
    {
        DialogSaveParameters->setWindowTitle(QApplication::translate("DialogSaveParameters", "\320\241\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DialogSaveParameters", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("DialogSaveParameters", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        saveAsCheckBox->setText(QApplication::translate("DialogSaveParameters", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", 0, QApplication::UnicodeUTF8));
        parameterSetLabel->setText(QApplication::translate("DialogSaveParameters", "Unf", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogSaveParameters: public Ui_DialogSaveParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSAVEPARAMETERS_H
