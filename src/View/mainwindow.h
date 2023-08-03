#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Controler/controler.h"
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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Neg_clicked();

    void on_pushButton_AC_clicked();

    void on_pushButton_CBB_clicked();

    void on_pushButton_CBD_clicked();

    void Convolution();

    void on_pushButton_CS_clicked();

private:
    Ui::MainWindow *ui;
    s21::Controler controler_;
    QString filename_;
    void FileReopen(const QString fname);
};

#endif // MAINWINDOW_H
