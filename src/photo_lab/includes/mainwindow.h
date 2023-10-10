#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <vector>

#include "controler.h"
#include "controler_button.h"
#include "matrix_mode.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(std::shared_ptr<s21::Controler> controler,
             QWidget* parent = nullptr);
  ~MainWindow();

 public slots:
  void RecieveData(std::vector<std::vector<double>> matrix);

 private slots:
  void UpdateImage();
  void on_pushButton_clicked();

  void on_pushButton_CS_clicked();

  void on_pushButton_Restart_clicked();

  void on_pushButton_MM_clicked();

  void on_pushButton_Save_clicked();

 private:
  Ui::MainWindow* ui;
  std::shared_ptr<MatrixMode> window_;
  std::shared_ptr<s21::Controler> controler_;
  std::vector<std::shared_ptr<s21::ContolerButton>> controler_btns_;
  // std::vector<std::shared_ptr<s21::ContolerButton>>
  // controler_convolution_btns_;
  QString filename_;
  void SetupView();
  std::shared_ptr<s21::ContolerButton> CreateControlerBtn(
      s21::CommandBase* command, const QString& text);
  void FileReopen(const QString fname);
};

#endif  // MAINWINDOW_H