/********************************************************************************
** Form generated from reading UI file 'formsetting.ui'
**
** Created: Sun 2. Jun 00:25:39 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMSETTING_H
#define UI_FORMSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormSetting
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *settingOptimisationTab;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *methodOptimisatonComboBox;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QRadioButton *errorAbsoluteRadioButton;
    QRadioButton *errorRelativeRadioButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *errorEpsSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpinBox *iterationCountSpinBox;
    QCheckBox *reportSaveCheckBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QRadioButton *reportFormatHtmlRadioButton;
    QRadioButton *reportFormatTextRadioButton;
    QRadioButton *reportFormatXmlRadionButton;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QButtonGroup *errorButtonGroup;
    QButtonGroup *reportFormatButtonGroup;

    void setupUi(QDialog *FormSetting)
    {
        if (FormSetting->objectName().isEmpty())
            FormSetting->setObjectName(QString::fromUtf8("FormSetting"));
        FormSetting->resize(376, 422);
        gridLayout = new QGridLayout(FormSetting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(FormSetting);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        settingOptimisationTab = new QWidget();
        settingOptimisationTab->setObjectName(QString::fromUtf8("settingOptimisationTab"));
        gridLayout_2 = new QGridLayout(settingOptimisationTab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(settingOptimisationTab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        methodOptimisatonComboBox = new QComboBox(settingOptimisationTab);
        methodOptimisatonComboBox->setObjectName(QString::fromUtf8("methodOptimisatonComboBox"));

        horizontalLayout_2->addWidget(methodOptimisatonComboBox);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(settingOptimisationTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        errorAbsoluteRadioButton = new QRadioButton(settingOptimisationTab);
        errorButtonGroup = new QButtonGroup(FormSetting);
        errorButtonGroup->setObjectName(QString::fromUtf8("errorButtonGroup"));
        errorButtonGroup->addButton(errorAbsoluteRadioButton);
        errorAbsoluteRadioButton->setObjectName(QString::fromUtf8("errorAbsoluteRadioButton"));

        verticalLayout->addWidget(errorAbsoluteRadioButton);

        errorRelativeRadioButton = new QRadioButton(settingOptimisationTab);
        errorButtonGroup->addButton(errorRelativeRadioButton);
        errorRelativeRadioButton->setObjectName(QString::fromUtf8("errorRelativeRadioButton"));
        errorRelativeRadioButton->setChecked(true);

        verticalLayout->addWidget(errorRelativeRadioButton);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(settingOptimisationTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        errorEpsSpinBox = new QSpinBox(settingOptimisationTab);
        errorEpsSpinBox->setObjectName(QString::fromUtf8("errorEpsSpinBox"));
        errorEpsSpinBox->setMinimum(1);
        errorEpsSpinBox->setMaximum(30);

        horizontalLayout->addWidget(errorEpsSpinBox);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(settingOptimisationTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        iterationCountSpinBox = new QSpinBox(settingOptimisationTab);
        iterationCountSpinBox->setObjectName(QString::fromUtf8("iterationCountSpinBox"));
        iterationCountSpinBox->setMinimum(1);
        iterationCountSpinBox->setMaximum(1000);
        iterationCountSpinBox->setValue(100);

        horizontalLayout_3->addWidget(iterationCountSpinBox);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        reportSaveCheckBox = new QCheckBox(settingOptimisationTab);
        reportSaveCheckBox->setObjectName(QString::fromUtf8("reportSaveCheckBox"));
        reportSaveCheckBox->setChecked(true);

        gridLayout_2->addWidget(reportSaveCheckBox, 4, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_5 = new QLabel(settingOptimisationTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        reportFormatHtmlRadioButton = new QRadioButton(settingOptimisationTab);
        reportFormatButtonGroup = new QButtonGroup(FormSetting);
        reportFormatButtonGroup->setObjectName(QString::fromUtf8("reportFormatButtonGroup"));
        reportFormatButtonGroup->addButton(reportFormatHtmlRadioButton);
        reportFormatHtmlRadioButton->setObjectName(QString::fromUtf8("reportFormatHtmlRadioButton"));
        reportFormatHtmlRadioButton->setChecked(true);

        verticalLayout_2->addWidget(reportFormatHtmlRadioButton);

        reportFormatTextRadioButton = new QRadioButton(settingOptimisationTab);
        reportFormatButtonGroup->addButton(reportFormatTextRadioButton);
        reportFormatTextRadioButton->setObjectName(QString::fromUtf8("reportFormatTextRadioButton"));

        verticalLayout_2->addWidget(reportFormatTextRadioButton);

        reportFormatXmlRadionButton = new QRadioButton(settingOptimisationTab);
        reportFormatButtonGroup->addButton(reportFormatXmlRadionButton);
        reportFormatXmlRadionButton->setObjectName(QString::fromUtf8("reportFormatXmlRadionButton"));

        verticalLayout_2->addWidget(reportFormatXmlRadionButton);


        gridLayout_2->addLayout(verticalLayout_2, 5, 0, 1, 1);

        tabWidget->addTab(settingOptimisationTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        cancelButton = new QPushButton(FormSetting);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_4->addWidget(cancelButton);

        saveButton = new QPushButton(FormSetting);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout_4->addWidget(saveButton);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        retranslateUi(FormSetting);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormSetting);
    } // setupUi

    void retranslateUi(QDialog *FormSetting)
    {
        FormSetting->setWindowTitle(QApplication::translate("FormSetting", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FormSetting", "\320\234\320\265\321\202\320\276\320\264:", 0, QApplication::UnicodeUTF8));
        methodOptimisatonComboBox->clear();
        methodOptimisatonComboBox->insertItems(0, QStringList()
         << QApplication::translate("FormSetting", "\320\245\321\203\320\272\320\260-\320\224\320\266\320\270\320\262\321\201\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormSetting", "\320\232\320\262\320\260\320\267\320\270\320\275\321\214\321\216\321\202\320\276\320\275\320\276\320\262\321\201\320\272\320\270\320\271", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FormSetting", "\320\235\320\260\320\270\321\201\320\272\320\276\321\200\320\265\320\271\321\210\320\265\320\263\320\276 \321\201\320\277\321\203\321\201\320\272\320\260", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("FormSetting", "\320\244\321\203\320\275\320\272\321\206\320\270\321\217 \320\276\321\210\320\270\320\261\320\272\320\270:", 0, QApplication::UnicodeUTF8));
        errorAbsoluteRadioButton->setText(QApplication::translate("FormSetting", "\320\220\320\261\321\201\320\276\320\273\321\216\321\202\320\275\320\260\321\217", 0, QApplication::UnicodeUTF8));
        errorRelativeRadioButton->setText(QApplication::translate("FormSetting", "\320\236\321\202\320\275\320\276\321\201\320\270\321\202\320\265\320\273\321\214\320\275\320\260\321\217", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FormSetting", "\320\237\320\276\320\263\321\200\320\265\321\210\320\275\320\276\321\201\321\202\321\214 \320\276\321\210\320\270\320\261\320\272\320\270:", 0, QApplication::UnicodeUTF8));
        errorEpsSpinBox->setSuffix(QString());
        errorEpsSpinBox->setPrefix(QApplication::translate("FormSetting", "1e-", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FormSetting", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\270\321\202\320\265\321\200\320\260\321\206\320\270\320\271:", 0, QApplication::UnicodeUTF8));
        reportSaveCheckBox->setText(QApplication::translate("FormSetting", "\320\241\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\214 \320\276\321\202\321\207\321\221\321\202", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FormSetting", "\320\244\320\276\321\200\320\274\320\260\321\202 \320\276\321\202\321\207\321\221\321\202\320\260:", 0, QApplication::UnicodeUTF8));
        reportFormatHtmlRadioButton->setText(QApplication::translate("FormSetting", "HTML", 0, QApplication::UnicodeUTF8));
        reportFormatTextRadioButton->setText(QApplication::translate("FormSetting", "\320\242\320\265\320\272\321\201\321\202", 0, QApplication::UnicodeUTF8));
        reportFormatXmlRadionButton->setText(QApplication::translate("FormSetting", "XML", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(settingOptimisationTab), QApplication::translate("FormSetting", "\320\236\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("FormSetting", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("FormSetting", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormSetting: public Ui_FormSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMSETTING_H
