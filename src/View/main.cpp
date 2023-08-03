#include "mainwindow.h"

#include <QApplication>
#include "../Model/Model.h"

int main(int argc, char *argv[])
{
    s21::Model *model {new s21::Model};
    QApplication a(argc, argv);
    MainWindow w(nullptr, model);
    w.show();
    return a.exec();
}
