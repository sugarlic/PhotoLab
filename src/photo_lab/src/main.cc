#include <QApplication>

#include "controler.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  std::shared_ptr<s21::Model> model(new s21::Model);
  std::shared_ptr<s21::Controler> controler(new s21::Controler(model));
  QApplication a(argc, argv);
  MainWindow w(controler);
  w.show();
  return a.exec();
}
