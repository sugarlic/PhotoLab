#include <QApplication>

#include "Model.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  auto model = new s21::Model;
  QApplication a(argc, argv);
  MainWindow w(nullptr, model);
  w.show();
  return a.exec();
}
