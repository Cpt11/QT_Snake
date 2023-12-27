#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.resize(w.getxx() * 50, w.getyy() * 50);
    w.show();
    return a.exec();
}
