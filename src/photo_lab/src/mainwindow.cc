#include "mainwindow.h"

#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <filesystem>

#include "ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<s21::Controler> controler,
                       QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      window_(new MatrixMode),
      controler_{controler} {
  ui->setupUi(this);
  SetupView();
}

MainWindow::~MainWindow() {
  delete ui;
  std::filesystem::remove("./output.bmp");
}

void MainWindow::FileReopen(const QString fname) {
  ui->label_out->setPixmap(QPixmap(fname));
  try {
    controler_->ReadImg(fname.toStdString());
  } catch (...) {
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
    controler_->ReadImg(filename_.toStdString());
  } catch (...) {
    std::cout << "Choose file";
  }
}

void MainWindow::on_pushButton_CS_clicked() {
  std::unique_ptr<QColorDialog> colorDialog(new QColorDialog());
  colorDialog->open();
  QColor color = colorDialog->getColor();
  if (color.isValid()) {
    controler_->ChannelSelection(color.red(), color.green(), color.blue());
    controler_->WriteImg("./output.bmp");
    FileReopen("./output.bmp");
  }
}

void MainWindow::on_pushButton_Restart_clicked() { FileReopen(filename_); }

void MainWindow::on_pushButton_MM_clicked() { window_->show(); }

void MainWindow::RecieveData(std::vector<std::vector<double>> matrix) {
  controler_->ArbitraryMatrixMode(matrix);
  controler_->WriteImg("./output.bmp");
  FileReopen("./output.bmp");
}

void MainWindow::on_pushButton_Save_clicked() {
  QString sourceFilePath = QDir::currentPath() + "/./output.bmp";
  QString destinationFilePath;
  QString filename = ui->lineEdit_Filename->text();

  QFileDialog fileDialog;
  fileDialog.setWindowTitle("Выберите директорию");
  fileDialog.setFileMode(QFileDialog::Directory);

  fileDialog.setDirectory("../../../../");

  if (fileDialog.exec()) {
    destinationFilePath =
        fileDialog.selectedFiles().at(0) + "/" + filename + ".bmp";
    QFile file(sourceFilePath);
    if (!file.rename(destinationFilePath)) {
      std::cout << "Не удалось перенести файл";
    }
  }
}

void MainWindow::SetupView() {
  std::vector<std::shared_ptr<s21::ContolerButton>> buttons;
  std::vector<std::shared_ptr<s21::ContolerButton>> convolution_buttons;
  std::vector<QString> convolution_names{"Embos",
                                         "Box blur",
                                         "Gaussian blur",
                                         "Laplacian filter",
                                         "Sobel filter left",
                                         "Sobel filter right",
                                         "Sobel filter combin"};
  buttons.push_back(
      CreateControlerBtn(new s21::CommandNegative(controler_), "Negative"));
  buttons.push_back(CreateControlerBtn(
      new s21::CommandAverageConversion(controler_), "Average conversion"));
  buttons.push_back(
      CreateControlerBtn(new s21::CommandConversionByBrightness(controler_),
                         "Conversion by brightness"));
  buttons.push_back(
      CreateControlerBtn(new s21::CommandConversionByDesaturation(controler_),
                         "Conversion by desaturation"));
  buttons.push_back(
      CreateControlerBtn(new s21::CommandConversionByDesaturation(controler_),
                         "Conversion by desaturation"));
  buttons.push_back(
      CreateControlerBtn(new s21::CommandConversionByDesaturation(controler_),
                         "Conversion by desaturation"));
  for (auto name : convolution_names)
    convolution_buttons.push_back(CreateControlerBtn(
        new s21::CommandConvolution(controler_, name.toStdString()), name));
  for (auto &but : buttons) {
    controler_btns_.push_back(but);
    ui->Controler_btns->addWidget(but.get());
  }
  for (auto &but : convolution_buttons) {
    controler_btns_.push_back(but);
    ui->Convolution_btns->addWidget(but.get());
  }
}

std::shared_ptr<s21::ContolerButton> MainWindow::CreateControlerBtn(
    s21::CommandBase *command, const QString &text) {
  auto command_ptr = std::unique_ptr<s21::CommandBase>(command);
  return std::make_shared<s21::ContolerButton>(std::move(command_ptr), text,
                                               this);
}
