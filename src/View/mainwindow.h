#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Controler/controler.h"
#include "matrix_mode.h"

#include <QMainWindow>
#include <QTableWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, s21::Model *model = nullptr);
    ~MainWindow();

public slots:
  void RecieveData(std::vector<std::vector<double>> matrix);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Neg_clicked();

    void on_pushButton_AC_clicked();

    void on_pushButton_CBB_clicked();

    void on_pushButton_CBD_clicked();

    void Convolution();

    void on_pushButton_CS_clicked();

    void on_pushButton_Restart_clicked();

    void on_pushButton_MM_clicked();

    void on_pushButton_Save_clicked();

private:
    Ui::MainWindow *ui;
    MatrixMode *window_;
    s21::Controler controler_;
    QString filename_;
    void FileReopen(const QString fname);
    QTableWidget* m_tableWidget;
};

#endif // MAINWINDOW_H
