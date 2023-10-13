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
  connect(window_.get(), &MatrixMode::SendData, this, &MainWindow::RecieveData);
  SetupView();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_MM_clicked() { window_->show(); }

void MainWindow::RecieveData(std::vector<std::vector<double>> matrix) {
  qDebug() << "Recieved";
  controler_->ArbitraryMatrixMode(matrix);
  UpdateImage();
}

void MainWindow::UpdateImage() {
  ui->label_out->setPixmap(QPixmap::fromImage(controler_->WriteImg()));
}

void MainWindow::RequestFileName() {
  ui->label_fname->setText(controler_->GetFilename().c_str());
}

void MainWindow::RequestImageSource() {
  controler_->Restart();
  ui->label->setPixmap(QPixmap::fromImage(controler_->WriteImg()));
}

void MainWindow::SetupView() {
  std::vector<std::shared_ptr<s21::ContolerButton>> buttons;
  std::vector<std::shared_ptr<s21::ContolerButton>> convolution_buttons;
  std::vector<QString> convolution_names{"Embos",
                                         "Sharpen",
                                         "Box blur",
                                         "Gaussian blur",
                                         "Laplacian filter",
                                         "Sobel filter left",
                                         "Sobel filter right"};
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
  for (auto name : convolution_names) {
    auto but = CreateControlerBtn(
        new s21::CommandConvolution(controler_, name.toStdString()), name);
    convolution_buttons.push_back(but);
  }

  auto color_container = std::make_shared<QColor>();
  auto color_command = std::make_unique<s21::CommandChannelSelection>(
      controler_, color_container);
  auto color_but = std::make_shared<s21::ChannelSelectionButton>(
      std::move(color_command), color_container, "Select color channel", this);
  buttons.push_back(color_but);
  controler_btns_.push_back(color_but);

  auto save_button =
      CreateControlerBtn(new s21::CommandSaveBMP(controler_), "Save image");
  auto open_button =
      CreateControlerBtn(new s21::CommandOpenBMP(controler_), "Open image");
  connect(open_button.get(), &s21::ContolerButton::Executed, this,
          &MainWindow::RequestFileName);
  connect(open_button.get(), &s21::ContolerButton::Executed, this,
          &MainWindow::RequestImageSource);
  buttons.push_back(save_button);
  buttons.push_back(open_button);

  for (auto &but : buttons) ui->Controler_btns->addWidget(but.get());
  for (auto &but : convolution_buttons)
    ui->Convolution_btns->addWidget(but.get());
}

std::shared_ptr<s21::ContolerButton> MainWindow::CreateControlerBtn(
    s21::CommandBase *command, const QString &text) {
  auto command_ptr = std::unique_ptr<s21::CommandBase>(command);
  auto btn_ptr =
      std::make_shared<s21::ContolerButton>(std::move(command_ptr), text, this);
  connect(btn_ptr.get(), &s21::ContolerButton::Executed, this,
          &MainWindow::UpdateImage);
  controler_btns_.push_back(btn_ptr);
  return btn_ptr;
}

void MainWindow::on_verticalSlider_Brightness_valueChanged(int value) {
  controler_->BrightnessChange(static_cast<float>(value) / 100);
  UpdateImage();
}

void MainWindow::on_verticalSlider_Contrast_valueChanged(int value) {
  controler_->ContrastChange(static_cast<float>(value) / 100);
  UpdateImage();
}

void MainWindow::on_verticalSlider_HSL_valueChanged(int value) {
  controler_->SaturationChange(1, 1, static_cast<float>(value) / 100);
  UpdateImage();
}

void MainWindow::on_verticalSlider_Lightness_valueChanged(int value) {
  controler_->SaturationChange(1, static_cast<float>(value) / 100, 1);
  UpdateImage();
}

void MainWindow::on_verticalSlider_Shade_valueChanged(int value) {
  controler_->SaturationChange(static_cast<float>(value) / 100, 1, 1);
  UpdateImage();
}
