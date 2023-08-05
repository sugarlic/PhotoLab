#include "matrix_mode.h"
#include "ui_matrix_mode.h"

MatrixMode::MatrixMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatrixMode)
{
    ui->setupUi(this);

}

MatrixMode::~MatrixMode()
{
    delete ui;
}

void MatrixMode::on_pushButton_clicked()
{
    rows_ = ui->textEdit_rows->toPlainText().toInt();
    cols_ = ui->textEdit_cols->toPlainText().toInt();
    if (rows_ > 1 && cols_ > 1 && rows_ <= 16 && cols_ <= 16) {
        ui->tableWidget->setRowCount(rows_);
        ui->tableWidget->setColumnCount(cols_);
    }
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            ui->tableWidget->setItem(i, j, new QTableWidgetItem("0"));

    for (int i = 0; i < rows_; ++i) {
        ui->tableWidget->setRowHeight(i, 50);
    }
    for (int i = 0; i < cols_; ++i) {
        ui->tableWidget->setColumnWidth(i, 50);
    }
}

void MatrixMode::on_pushButton_Send_clicked()
{
    if (rows_ > 1 && cols_ > 1) {
        std::vector<std::vector<double>> data(rows_, std::vector<double>(cols_));
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data[i][j] = ui->tableWidget->item(i, j)->text().toDouble();
            }
        }
        emit SendData(data);
    }
}

