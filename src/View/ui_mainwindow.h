/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_AC;
    QPushButton *pushButton_Restart;
    QPushButton *pushButton_CS;
    QPushButton *pushButton_CBD;
    QPushButton *pushButton_Neg;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_CBB;
    QLineEdit *lineEdit_Filename;
    QLabel *label_fname;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QPushButton *pushButton_SFR;
    QPushButton *pushButton_SFC;
    QPushButton *pushButton_SFL;
    QPushButton *pushButton_LF;
    QPushButton *pushButton_GausB;
    QPushButton *pushButton_Embos;
    QPushButton *pushButton_BB;
    QPushButton *pushButton_GB;
    QPushButton *pushButton_MM;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_out;
    QLabel *label;
    QMenuBar *menubar;
    QButtonGroup *ConvolutionGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1601, 755);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(1380, 10, 211, 351));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(false);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_AC = new QPushButton(gridLayoutWidget);
        pushButton_AC->setObjectName(QString::fromUtf8("pushButton_AC"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_AC->sizePolicy().hasHeightForWidth());
        pushButton_AC->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_AC, 5, 0, 1, 1);

        pushButton_Restart = new QPushButton(gridLayoutWidget);
        pushButton_Restart->setObjectName(QString::fromUtf8("pushButton_Restart"));
        sizePolicy1.setHeightForWidth(pushButton_Restart->sizePolicy().hasHeightForWidth());
        pushButton_Restart->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_Restart, 11, 0, 1, 1);

        pushButton_CS = new QPushButton(gridLayoutWidget);
        pushButton_CS->setObjectName(QString::fromUtf8("pushButton_CS"));
        sizePolicy.setHeightForWidth(pushButton_CS->sizePolicy().hasHeightForWidth());
        pushButton_CS->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_CS, 10, 0, 1, 1);

        pushButton_CBD = new QPushButton(gridLayoutWidget);
        pushButton_CBD->setObjectName(QString::fromUtf8("pushButton_CBD"));
        sizePolicy.setHeightForWidth(pushButton_CBD->sizePolicy().hasHeightForWidth());
        pushButton_CBD->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_CBD, 8, 0, 1, 1);

        pushButton_Neg = new QPushButton(gridLayoutWidget);
        pushButton_Neg->setObjectName(QString::fromUtf8("pushButton_Neg"));
        sizePolicy1.setHeightForWidth(pushButton_Neg->sizePolicy().hasHeightForWidth());
        pushButton_Neg->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_Neg, 4, 0, 1, 1);

        pushButton_Save = new QPushButton(gridLayoutWidget);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));
        sizePolicy1.setHeightForWidth(pushButton_Save->sizePolicy().hasHeightForWidth());
        pushButton_Save->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_Save, 2, 0, 1, 1);

        pushButton_CBB = new QPushButton(gridLayoutWidget);
        pushButton_CBB->setObjectName(QString::fromUtf8("pushButton_CBB"));
        sizePolicy1.setHeightForWidth(pushButton_CBB->sizePolicy().hasHeightForWidth());
        pushButton_CBB->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_CBB, 6, 0, 1, 1);

        lineEdit_Filename = new QLineEdit(gridLayoutWidget);
        lineEdit_Filename->setObjectName(QString::fromUtf8("lineEdit_Filename"));
        sizePolicy.setHeightForWidth(lineEdit_Filename->sizePolicy().hasHeightForWidth());
        lineEdit_Filename->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_Filename, 3, 0, 1, 1);

        label_fname = new QLabel(centralwidget);
        label_fname->setObjectName(QString::fromUtf8("label_fname"));
        label_fname->setGeometry(QRect(630, 20, 391, 51));
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(1380, 370, 211, 351));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(false);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        pushButton_SFR = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup = new QButtonGroup(MainWindow);
        ConvolutionGroup->setObjectName(QString::fromUtf8("ConvolutionGroup"));
        ConvolutionGroup->addButton(pushButton_SFR);
        pushButton_SFR->setObjectName(QString::fromUtf8("pushButton_SFR"));
        sizePolicy1.setHeightForWidth(pushButton_SFR->sizePolicy().hasHeightForWidth());
        pushButton_SFR->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_SFR, 7, 0, 1, 1);

        pushButton_SFC = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup->addButton(pushButton_SFC);
        pushButton_SFC->setObjectName(QString::fromUtf8("pushButton_SFC"));
        sizePolicy1.setHeightForWidth(pushButton_SFC->sizePolicy().hasHeightForWidth());
        pushButton_SFC->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_SFC, 8, 0, 1, 1);

        pushButton_SFL = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup->addButton(pushButton_SFL);
        pushButton_SFL->setObjectName(QString::fromUtf8("pushButton_SFL"));
        sizePolicy1.setHeightForWidth(pushButton_SFL->sizePolicy().hasHeightForWidth());
        pushButton_SFL->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_SFL, 6, 0, 1, 1);

        pushButton_LF = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup->addButton(pushButton_LF);
        pushButton_LF->setObjectName(QString::fromUtf8("pushButton_LF"));
        sizePolicy1.setHeightForWidth(pushButton_LF->sizePolicy().hasHeightForWidth());
        pushButton_LF->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_LF, 5, 0, 1, 1);

        pushButton_GausB = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup->addButton(pushButton_GausB);
        pushButton_GausB->setObjectName(QString::fromUtf8("pushButton_GausB"));
        sizePolicy1.setHeightForWidth(pushButton_GausB->sizePolicy().hasHeightForWidth());
        pushButton_GausB->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_GausB, 4, 0, 1, 1);

        pushButton_Embos = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup->addButton(pushButton_Embos);
        pushButton_Embos->setObjectName(QString::fromUtf8("pushButton_Embos"));
        sizePolicy1.setHeightForWidth(pushButton_Embos->sizePolicy().hasHeightForWidth());
        pushButton_Embos->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_Embos, 1, 0, 1, 1);

        pushButton_BB = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup->addButton(pushButton_BB);
        pushButton_BB->setObjectName(QString::fromUtf8("pushButton_BB"));
        sizePolicy1.setHeightForWidth(pushButton_BB->sizePolicy().hasHeightForWidth());
        pushButton_BB->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_BB, 3, 0, 1, 1);

        pushButton_GB = new QPushButton(gridLayoutWidget_2);
        ConvolutionGroup->addButton(pushButton_GB);
        pushButton_GB->setObjectName(QString::fromUtf8("pushButton_GB"));
        sizePolicy1.setHeightForWidth(pushButton_GB->sizePolicy().hasHeightForWidth());
        pushButton_GB->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_GB, 2, 0, 1, 1);

        pushButton_MM = new QPushButton(gridLayoutWidget_2);
        pushButton_MM->setObjectName(QString::fromUtf8("pushButton_MM"));
        sizePolicy1.setHeightForWidth(pushButton_MM->sizePolicy().hasHeightForWidth());
        pushButton_MM->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButton_MM, 9, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(20, 10, 1341, 711));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_out = new QLabel(gridLayoutWidget_3);
        label_out->setObjectName(QString::fromUtf8("label_out"));
        label_out->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_out->sizePolicy().hasHeightForWidth());
        label_out->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_out, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1601, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Simple filtrs", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open file", nullptr));
        pushButton_AC->setText(QCoreApplication::translate("MainWindow", "AverageConversion", nullptr));
        pushButton_Restart->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        pushButton_CS->setText(QCoreApplication::translate("MainWindow", "Chanel selection", nullptr));
        pushButton_CBD->setText(QCoreApplication::translate("MainWindow", "Conversion by desaturation", nullptr));
        pushButton_Neg->setText(QCoreApplication::translate("MainWindow", "Negative", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("MainWindow", "Save image", nullptr));
        pushButton_CBB->setText(QCoreApplication::translate("MainWindow", "Conversion by brightness", nullptr));
        lineEdit_Filename->setText(QCoreApplication::translate("MainWindow", "File name", nullptr));
        label_fname->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Convolution filters", nullptr));
        pushButton_SFR->setText(QCoreApplication::translate("MainWindow", "Sobel filter right", nullptr));
        pushButton_SFC->setText(QCoreApplication::translate("MainWindow", "Sobel filter combin", nullptr));
        pushButton_SFL->setText(QCoreApplication::translate("MainWindow", "Sobel filter left", nullptr));
        pushButton_LF->setText(QCoreApplication::translate("MainWindow", "Laplacian filter", nullptr));
        pushButton_GausB->setText(QCoreApplication::translate("MainWindow", "Gaussian blur", nullptr));
        pushButton_Embos->setText(QCoreApplication::translate("MainWindow", "Embos", nullptr));
        pushButton_BB->setText(QCoreApplication::translate("MainWindow", "Box blur", nullptr));
        pushButton_GB->setText(QCoreApplication::translate("MainWindow", "Gaussian blur", nullptr));
        pushButton_MM->setText(QCoreApplication::translate("MainWindow", "Matrix mode", nullptr));
        label_out->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
