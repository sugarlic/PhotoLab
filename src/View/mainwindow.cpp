#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent, s21::Model *model)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controler_{model}
{
    ui->setupUi(this);
    for (auto it : ui->ConvolutionGroup->buttons()) connect(it, SIGNAL(clicked()), this, SLOT(Convolution()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FileReopen(const QString fname) {
    ui->label->setPixmap(QPixmap(fname));
    try {
        controler_.ReadImg(fname.toStdString());
    } catch(std::__nested<std::runtime_error>) {
        qDebug() << "Choose file";
    }
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog fileDialog;
    fileDialog.setWindowTitle("Выберите файл");
    fileDialog.setFileMode(QFileDialog::ExistingFile);

    fileDialog.setDirectory("../../../../");

    if (fileDialog.exec()) {
        filename_ = fileDialog.selectedFiles().at(0);
        ui->label_fname->setText(filename_);
    }

    FileReopen(filename_);
}

void MainWindow::on_pushButton_Neg_clicked()
{
    controler_.Negative();
    controler_.WriteImg("output.bmp");
    FileReopen("output.bmp");
}

void MainWindow::on_pushButton_AC_clicked()
{
    controler_.AverageConversion();
    controler_.WriteImg("output.bmp");
    FileReopen("output.bmp");
}

void MainWindow::on_pushButton_CBB_clicked()
{
    controler_.ConversionByBrightness();
    controler_.WriteImg("output.bmp");
    FileReopen("output.bmp");
}


void MainWindow::on_pushButton_CBD_clicked()
{
    controler_.ConversionByDesaturation();
    controler_.WriteImg("output.bmp");
    FileReopen("output.bmp");
}

void MainWindow::Convolution() {
    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "Sobel filter combin") controler_.SobelFilterCombin();
    else controler_.Convolution(button->text().toStdString());
    controler_.WriteImg("output.bmp");
    FileReopen("output.bmp");
}

void MainWindow::on_pushButton_CS_clicked()
{
    QColorDialog *colorDialog = new QColorDialog();
    colorDialog->open();
    QColor color = colorDialog->getColor();
    if (color.isValid()) {
       controler_.ChannelSelection(color.red(), color.green(), color.blue());
       controler_.WriteImg("output.bmp");
       FileReopen("output.bmp");
    }
    delete(colorDialog);
}
