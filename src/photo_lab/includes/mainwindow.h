#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <vector>

#include "controler.h"
#include "controler_button.h"
#include "controler_slider.h"
#include "matrix_mode.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
#include "ui_mainwindow.h"
namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(std::shared_ptr<Controler> controler, QWidget* parent = nullptr);
  ~MainWindow();

 public slots:
  void RecieveData(std::vector<std::vector<double>> matrix);

 private slots:
  void UpdateImage();
  void RequestFileName();
  void RequestImageSource();
  void SelectColorChannel();
  void on_pushButton_MM_clicked();

 private:
  ::Ui::MainWindow* ui;

  std::shared_ptr<MatrixMode> window_;
  std::shared_ptr<Controler> controler_;
  std::vector<std::shared_ptr<ControlerPushButton>> controler_btns_;
  std::vector<std::shared_ptr<ControlerSlider>> controler_sliders_;
  QString filename_;
  void SetupView();
  std::shared_ptr<ControlerPushButton> CreateControlerBtn(CommandBase* command,
                                                          const QString& text);
  std::shared_ptr<ControlerSlider> CreateControlerSlider(
      CommandWithValueBase<float>* command, float delimeter = 100);
  void resizeEvent(QResizeEvent* event) override {
    auto l1 = ui->Source_Image_L;
    auto l2 = ui->Filtered_Image_L;
    auto map = QPixmap::fromImage(controler_->GetSource().scaled(l1->size()));
    l1->setPixmap(map);
    map = QPixmap::fromImage(controler_->WriteImg().scaled(l2->size()));
    l2->setPixmap(map);
    QMainWindow::resizeEvent(event);
  }
};
}  // namespace s21

#endif  // MAINWINDOW_H
