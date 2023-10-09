#ifndef MATRIX_MODE_H
#define MATRIX_MODE_H

#include <QDialog>
#include <vector>

namespace Ui {
class MatrixMode;
}

class MatrixMode : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixMode(QWidget *parent = nullptr);
    ~MatrixMode();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Send_clicked();

signals:
  void SendData(std::vector<std::vector<double>>);

private:
    Ui::MatrixMode *ui;
    int rows_{};
    int cols_{};
};

#endif // MATRIX_MODE_H
