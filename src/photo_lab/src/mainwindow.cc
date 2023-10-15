#include "mainwindow.h"

#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <filesystem>
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
  auto map = QPixmap::fromImage(
      controler_->WriteImg().scaled(ui->Filtered_Image_L->size()));
  ui->Filtered_Image_L->setPixmap(map);
}

void MainWindow::RequestFileName() {
  ui->Filename_L->setText(controler_->GetFilename().c_str());
}

void MainWindow::RequestImageSource() {
  controler_->Restart();
  auto map = QPixmap::fromImage(
      controler_->WriteImg().scaled(ui->Source_Image_L->size()));
  ui->Source_Image_L->setPixmap(map);
}

void MainWindow::SelectColorChannel() {
  auto but = (QRadioButton *)(sender());
  s21::Model::ColorChannel channel = s21::Model::kNone;
  if (but == ui->ChannelNone_B) channel = s21::Model::kNone;
  if (but == ui->ChannelRed_B) channel = s21::Model::kRed;
  if (but == ui->ChannelGreen_B) channel = s21::Model::kGreen;
  if (but == ui->ChannelBlue_B) channel = s21::Model::kBlue;
  controler_->ChannelSelection(channel);
}

void MainWindow::SetupView() {
  using ctrl_btn_vec = std::vector<std::shared_ptr<s21::ControlerPushButton>>;
  ctrl_btn_vec buttons;
  ctrl_btn_vec convolution_buttons;

  auto connect_to_action = [](QAction *act,
                              std::shared_ptr<s21::ControlerPushButton> but,
                              ctrl_btn_vec &arr) {
    connect(act, &QAction::triggered, but.get(), &QPushButton::click);
    arr.push_back(but);
  };

  for (auto but : ui->ChannelButtons->buttons()) {
    connect(but, &QRadioButton::clicked, this, &MainWindow::SelectColorChannel);
    connect(but, &QRadioButton::clicked, this, &MainWindow::UpdateImage);
  }

  connect_to_action(
      ui->actionNegative,
      CreateControlerBtn(new s21::CommandNegative(controler_), "Negative"),
      buttons);
  connect_to_action(
      ui->actionAverage_conversion,
      CreateControlerBtn(new s21::CommandAverageConversion(controler_),
                         "Average conversion"),
      buttons);
  connect_to_action(
      ui->actionBy_brightness,
      CreateControlerBtn(new s21::CommandConversionByBrightness(controler_),
                         "Conversion by brightness"),
      buttons);
  connect_to_action(
      ui->actionBy_desaturation,
      CreateControlerBtn(new s21::CommandConversionByDesaturation(controler_),
                         "Conversion by desaturation"),
      buttons);
  connect_to_action(
      ui->actionSober_combined,
      CreateControlerBtn(new s21::CommandSobelFilterCombin(controler_),
                         "Sobel filter combin"),
      buttons);

  connect_to_action(
      ui->actionEmbos,
      CreateControlerBtn(new s21::CommandConvolution(controler_, "Embos"),
                         "Embos"),
      convolution_buttons);
  connect_to_action(
      ui->actionSharpen,
      CreateControlerBtn(new s21::CommandConvolution(controler_, "Sharpen"),
                         "Sharpen"),
      convolution_buttons);
  connect_to_action(
      ui->actionBox_blur,
      CreateControlerBtn(new s21::CommandConvolution(controler_, "Box blur"),
                         "Box blur"),
      convolution_buttons);
  connect_to_action(ui->actionGaussian_blur,
                    CreateControlerBtn(new s21::CommandConvolution(
                                           controler_, "Gaussian blur"),
                                       "Gaussian blur"),
                    convolution_buttons);
  connect_to_action(ui->actionLaplacian_filter,
                    CreateControlerBtn(new s21::CommandConvolution(
                                           controler_, "Laplacian filter"),
                                       "Laplacian filter"),
                    convolution_buttons);
  connect_to_action(ui->actionSober_filter_left,
                    CreateControlerBtn(new s21::CommandConvolution(
                                           controler_, "Sobel filter left"),
                                       "Sobel filter left"),
                    convolution_buttons);
  connect_to_action(ui->actionSober_filter_right,
                    CreateControlerBtn(new s21::CommandConvolution(
                                           controler_, "Sobel filter right"),
                                       "Sobel filter right"),
                    convolution_buttons);
  auto reset_but1 =
      CreateControlerBtn(new s21::CommandRestart(controler_), "Reset filters");
  auto reset_but2 =
      CreateControlerBtn(new s21::CommandRestart(controler_), "Reset filters");
  auto reset_but3 =
      CreateControlerBtn(new s21::CommandRestart(controler_), "Reset filters");

  // auto color_container = std::make_shared<QColor>();
  // auto color_command = std::make_unique<s21::CommandChannelSelection>(
  //     controler_, color_container);
  // auto color_but = std::make_shared<s21::ChannelSelectionButton>(
  //     std::move(color_command), color_container, "Select color channel",
  //     this);
  // connect(color_but.get(), &s21::ChannelSelectionButton::Executed, this,
  //         &MainWindow::UpdateImage);
  // buttons.push_back(color_but);
  // controler_btns_.push_back(color_but);

  auto save_button =
      CreateControlerBtn(new s21::CommandSaveBMP(controler_), "Save image");
  auto open_button =
      CreateControlerBtn(new s21::CommandOpenBMP(controler_), "Open image");
  connect(open_button.get(), &s21::ControlerPushButton::Executed, this,
          &MainWindow::RequestFileName);
  connect(open_button.get(), &s21::ControlerPushButton::Executed, this,
          &MainWindow::RequestImageSource);
  auto matrix_but = ui->Main_Buttons->itemAt(0)->widget();
  ui->Main_Buttons->removeWidget(matrix_but);
  ui->Main_Buttons->addWidget(open_button.get(), 0, 0);
  ui->Main_Buttons->addWidget(save_button.get(), 1, 0);
  ui->Main_Buttons->addWidget(matrix_but, 2, 0);
  ui->Main_Buttons->addWidget(reset_but1.get(), 3, 0);
  for (auto &but : buttons) ui->Controler_btns->addWidget(but.get());
  for (auto &but : convolution_buttons)
    ui->Convolution_btns->addWidget(but.get());
  ui->Convolution_btns->addWidget(reset_but2.get());
  ui->Controler_btns->addWidget(reset_but3.get());
}

std::shared_ptr<s21::ControlerPushButton> MainWindow::CreateControlerBtn(
    s21::CommandBase *command, const QString &text) {
  auto command_ptr = std::unique_ptr<s21::CommandBase>(command);
  auto btn_ptr = std::make_shared<s21::ControlerPushButton>(
      std::move(command_ptr), text, this);
  connect(btn_ptr.get(), &s21::ControlerPushButton::Executed, this,
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
