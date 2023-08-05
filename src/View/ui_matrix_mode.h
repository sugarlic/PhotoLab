/********************************************************************************
** Form generated from reading UI file 'matrix_mode.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIX_MODE_H
#define UI_MATRIX_MODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatrixMode
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit_rows;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEdit_cols;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QPushButton *pushButton_Send;

    void setupUi(QDialog *MatrixMode)
    {
        if (MatrixMode->objectName().isEmpty())
            MatrixMode->setObjectName(QString::fromUtf8("MatrixMode"));
        MatrixMode->resize(764, 566);
        gridLayoutWidget = new QWidget(MatrixMode);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(210, 10, 341, 31));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        textEdit_rows = new QTextEdit(gridLayoutWidget);
        textEdit_rows->setObjectName(QString::fromUtf8("textEdit_rows"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit_rows->sizePolicy().hasHeightForWidth());
        textEdit_rows->setSizePolicy(sizePolicy);
        textEdit_rows->setMinimumSize(QSize(91, 41));
        textEdit_rows->setMaximumSize(QSize(91, 41));

        gridLayout->addWidget(textEdit_rows, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        textEdit_cols = new QTextEdit(gridLayoutWidget);
        textEdit_cols->setObjectName(QString::fromUtf8("textEdit_cols"));
        sizePolicy.setHeightForWidth(textEdit_cols->sizePolicy().hasHeightForWidth());
        textEdit_cols->setSizePolicy(sizePolicy);
        textEdit_cols->setMinimumSize(QSize(91, 41));
        textEdit_cols->setMaximumSize(QSize(91, 41));

        gridLayout->addWidget(textEdit_cols, 0, 4, 1, 1);

        pushButton = new QPushButton(MatrixMode);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(330, 50, 100, 32));
        tableWidget = new QTableWidget(MatrixMode);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 80, 721, 441));
        pushButton_Send = new QPushButton(MatrixMode);
        pushButton_Send->setObjectName(QString::fromUtf8("pushButton_Send"));
        pushButton_Send->setGeometry(QRect(330, 530, 100, 32));

        retranslateUi(MatrixMode);

        QMetaObject::connectSlotsByName(MatrixMode);
    } // setupUi

    void retranslateUi(QDialog *MatrixMode)
    {
        MatrixMode->setWindowTitle(QCoreApplication::translate("MatrixMode", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("MatrixMode", "rows", nullptr));
        label_2->setText(QCoreApplication::translate("MatrixMode", "cols", nullptr));
        pushButton->setText(QCoreApplication::translate("MatrixMode", "Set", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("MatrixMode", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixMode: public Ui_MatrixMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIX_MODE_H
