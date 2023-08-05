#include "mainwindow.h"

#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <filesystem>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, s21::Model *model)
    : QMainWindow(parent), ui(new Ui::MainWindow), controler_{model} {
  window_ = new MatrixMode;
  ui->setupUi(this);

  for (auto it : ui->ConvolutionGroup->buttons())
    connect(it, SIGNAL(clicked()), this, SLOT(Convolution()));
  connect(window_, SIGNAL(SendData(std::vector<std::vector<double>>)), this,
          SLOT(RecieveData(std::vector<std::vector<double>>)));
}

MainWindow::~MainWindow() {
  delete ui;
  delete window_;
      std::filesystem::remove("output.bmp");
}

void MainWindow::FileReopen(const QString fname) {
  ui->label_out->setPixmap(QPixmap(fname));
  try {
    controler_.ReadImg(fname.toStdString());
  } catch (std::__nested<std::runtime_error>) {
    std::cout << "Choose file";
  }
}

void MainWindow::on_pushButton_clicked() {
  QFileDialog fileDialog;
  fileDialog.setWindowTitle("Выберите директорию");
  fileDialog.setFileMode(QFileDialog::ExistingFile);

  fileDialog.setDirectory("../../../../");

  if (fileDialog.exec()) {
    filename_ = fileDialog.selectedFiles().at(0);
    ui->label_fname->setText(filename_);
  }

  ui->label->setPixmap(QPixmap(filename_));
  try {
    controler_.ReadImg(filename_.toStdString());
  } catch (std::__nested<std::runtime_error>) {
    std::cout << "Choose file";
  }
}

void MainWindow::on_pushButton_Neg_clicked() {
  controler_.Negative();
  controler_.WriteImg("output.bmp");
  FileReopen("output.bmp");
}

void MainWindow::on_pushButton_AC_clicked() {
  controler_.AverageConversion();
  controler_.WriteImg("output.bmp");
  FileReopen("output.bmp");
}

void MainWindow::on_pushButton_CBB_clicked() {
  controler_.ConversionByBrightness();
  controler_.WriteImg("output.bmp");
  FileReopen("output.bmp");
}

void MainWindow::on_pushButton_CBD_clicked() {
  controler_.ConversionByDesaturation();
  controler_.WriteImg("output.bmp");
  FileReopen("output.bmp");
}

void MainWindow::Convolution() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "Sobel filter combin")
    controler_.SobelFilterCombin();
  else
    controler_.Convolution(button->text().toStdString());
  controler_.WriteImg("output.bmp");
  FileReopen("output.bmp");
}

void MainWindow::on_pushButton_CS_clicked() {
  QColorDialog *colorDialog = new QColorDialog();
  colorDialog->open();
  QColor color = colorDialog->getColor();
  if (color.isValid()) {
    controler_.ChannelSelection(color.red(), color.green(), color.blue());
    controler_.WriteImg("output.bmp");
    FileReopen("output.bmp");
  }
  delete (colorDialog);
}

void MainWindow::on_pushButton_Restart_clicked() { FileReopen(filename_); }

void MainWindow::on_pushButton_MM_clicked() { window_->show(); }

void MainWindow::RecieveData(std::vector<std::vector<double>> matrix) {
  controler_.ArbitraryMatrixMode(matrix);
  controler_.WriteImg("output.bmp");
  FileReopen("output.bmp");
}

void MainWindow::on_pushButton_Save_clicked() {
  QString sourceFilePath = QDir::currentPath() + "/output.bmp";
  QString destinationFilePath;
  QString filename = ui->lineEdit_Filename->text();

  QFileDialog fileDialog;
  fileDialog.setWindowTitle("Выберите директорию");
  fileDialog.setFileMode(QFileDialog::Directory);

  fileDialog.setDirectory("../../../../");

  if (fileDialog.exec()) {
    destinationFilePath = fileDialog.selectedFiles().at(0) + "/" + filename + ".bmp";
    QFile file(sourceFilePath);
    if (!file.rename(destinationFilePath)) {
      std::cout<< "Не удалось перенести файл";
    }
  }
}
