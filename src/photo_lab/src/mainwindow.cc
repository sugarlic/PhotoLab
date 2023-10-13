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
  connect(window_.get(), &MatrixMode::SendData,
          this, &MainWindow::RecieveData);
  SetupView();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  QFileDialog fileDialog;
  fileDialog.setWindowTitle("Выберите директорию");
  fileDialog.setFileMode(QFileDialog::ExistingFile);

  fileDialog.setDirectory("../");

  if (fileDialog.exec()) {
    filename_ = fileDialog.selectedFiles().at(0);
    ui->label_fname->setText(filename_);
  }

  ui->label->setPixmap(QPixmap(filename_));
  try {
    controler_->ReadImg(filename_.toStdString());
    UpdateImage();
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
    UpdateImage();
  }
}

void MainWindow::on_pushButton_Restart_clicked() {
  controler_->Restart();
  UpdateImage();
}

void MainWindow::on_pushButton_MM_clicked() { window_->show(); }

void MainWindow::RecieveData(std::vector<std::vector<double>> matrix) {
  qDebug()<<"Recieved";
  controler_->ArbitraryMatrixMode(matrix);
  UpdateImage();
}

void MainWindow::UpdateImage() {
  try {
    ui->label_out->setPixmap(QPixmap::fromImage(controler_->WriteImg()));
  } catch (...) {
    return;
  }
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
  for (auto &but : controler_btns_) {
    connect(but.get(), SIGNAL(clicked()), this, SLOT(UpdateImage()));
  }
}

std::shared_ptr<s21::ContolerButton> MainWindow::CreateControlerBtn(
    s21::CommandBase *command, const QString &text) {
  auto command_ptr = std::unique_ptr<s21::CommandBase>(command);
  return std::make_shared<s21::ContolerButton>(std::move(command_ptr), text,
                                               this);
}

void MainWindow::on_verticalSlider_Brightness_valueChanged(int value)
{
    controler_->BrightnessChange(static_cast<float>(value)/100);
    UpdateImage();
}


void MainWindow::on_verticalSlider_Contrast_valueChanged(int value)
{
    controler_->ContrastChange(static_cast<float>(value)/100);
    UpdateImage();
}

