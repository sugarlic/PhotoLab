#include "mainwindow.h"

#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <filesystem>
namespace s21 {
MainWindow::MainWindow(std::shared_ptr<Controler> controler, QWidget *parent)
    : QMainWindow(parent),
      ui(new ::Ui::MainWindow),
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
  Model::ColorChannel channel = Model::kNone;
  if (but == ui->ChannelNone_B) channel = Model::kNone;
  if (but == ui->ChannelRed_B) channel = Model::kRed;
  if (but == ui->ChannelGreen_B) channel = Model::kGreen;
  if (but == ui->ChannelBlue_B) channel = Model::kBlue;
  controler_->ChannelSelection(channel);
}

void MainWindow::SetupView() {
  using ctrl_btn_vec = std::vector<std::shared_ptr<ControlerPushButton>>;
  ctrl_btn_vec buttons;
  ctrl_btn_vec convolution_buttons;

  auto connect_to_action = [](QAction *act,
                              std::shared_ptr<ControlerPushButton> but,
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
      CreateControlerBtn(new CommandNegative(controler_), "Negative"), buttons);
  connect_to_action(ui->actionAverage_conversion,
                    CreateControlerBtn(new CommandAverageConversion(controler_),
                                       "Average conversion"),
                    buttons);
  connect_to_action(
      ui->actionBy_brightness,
      CreateControlerBtn(new CommandConversionByBrightness(controler_),
                         "Conversion by brightness"),
      buttons);
  connect_to_action(
      ui->actionBy_desaturation,
      CreateControlerBtn(new CommandConversionByDesaturation(controler_),
                         "Conversion by desaturation"),
      buttons);
  connect_to_action(ui->actionSober_combined,
                    CreateControlerBtn(new CommandSobelFilterCombin(controler_),
                                       "Sobel filter combin"),
                    buttons);
  connect_to_action(ui->actionToning,
                    CreateControlerBtn(new CommandToning(controler_), "Toning"),
                    buttons);

  connect_to_action(
      ui->actionEmbos,
      CreateControlerBtn(new CommandConvolution(controler_, "Embos"), "Embos"),
      convolution_buttons);
  connect_to_action(
      ui->actionSharpen,
      CreateControlerBtn(new CommandConvolution(controler_, "Sharpen"),
                         "Sharpen"),
      convolution_buttons);
  connect_to_action(
      ui->actionBox_blur,
      CreateControlerBtn(new CommandConvolution(controler_, "Box blur"),
                         "Box blur"),
      convolution_buttons);
  connect_to_action(
      ui->actionGaussian_blur,
      CreateControlerBtn(new CommandConvolution(controler_, "Gaussian blur"),
                         "Gaussian blur"),
      convolution_buttons);
  connect_to_action(
      ui->actionLaplacian_filter,
      CreateControlerBtn(new CommandConvolution(controler_, "Laplacian filter"),
                         "Laplacian filter"),
      convolution_buttons);
  connect_to_action(ui->actionSober_filter_left,
                    CreateControlerBtn(
                        new CommandConvolution(controler_, "Sobel filter left"),
                        "Sobel filter left"),
                    convolution_buttons);
  connect_to_action(ui->actionSober_filter_right,
                    CreateControlerBtn(new CommandConvolution(
                                           controler_, "Sobel filter right"),
                                       "Sobel filter right"),
                    convolution_buttons);
  auto reset_but1 =
      CreateControlerBtn(new CommandRestart(controler_), "Reset filters");
  auto reset_but2 =
      CreateControlerBtn(new CommandRestart(controler_), "Reset filters");
  auto reset_but3 =
      CreateControlerBtn(new CommandRestart(controler_), "Reset filters");
  auto save_button =
      CreateControlerBtn(new CommandSaveBMP(controler_), "Save image");
  auto open_button =
      CreateControlerBtn(new CommandOpenBMP(controler_), "Open image");
  connect(open_button.get(), &ControlerPushButton::Executed, this,
          &MainWindow::RequestFileName);
  connect(open_button.get(), &ControlerPushButton::Executed, this,
          &MainWindow::RequestImageSource);
  auto slider =
      CreateControlerSlider(new CommandSetSaturation(controler_)).get();
  slider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  ui->HSL_Grid->addWidget(slider, 1, 0);
  slider = CreateControlerSlider(new CommandSetLightness(controler_)).get();
  slider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  ui->HSL_Grid->addWidget(slider, 1, 1);
  slider = CreateControlerSlider(new CommandSetShade(controler_)).get();
  slider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  ui->HSL_Grid->addWidget(slider, 1, 2);

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

std::shared_ptr<ControlerPushButton> MainWindow::CreateControlerBtn(
    CommandBase *command, const QString &text) {
  auto command_ptr = std::unique_ptr<CommandBase>(command);
  auto btn_ptr =
      std::make_shared<ControlerPushButton>(std::move(command_ptr), text, this);
  connect(btn_ptr.get(), &ControlerPushButton::Executed, this,
          &MainWindow::UpdateImage);
  controler_btns_.push_back(btn_ptr);
  return btn_ptr;
}
std::shared_ptr<ControlerSlider> MainWindow::CreateControlerSlider(
    CommandWithValueBase<float> *command, float delimeter) {
  auto command_ptr = std::unique_ptr<CommandWithValueBase<float>>(command);
  auto slider_ptr = std::make_shared<ControlerSlider>(std::move(command_ptr),
                                                      delimeter, this);
  connect(slider_ptr.get(), &ControlerSlider::Executed, this,
          &MainWindow::UpdateImage);
  controler_sliders_.push_back(slider_ptr);
  return slider_ptr;
}
}  // namespace s21