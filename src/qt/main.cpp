// #include <iostream>

#include <locale.h>

#include <QApplication>

#include "mainwindow.h"
using namespace std;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  setlocale(LC_NUMERIC, "C");
  MainWindow mw;
  mw.show();
  return app.exec();
}
