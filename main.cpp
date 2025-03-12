#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<Wrestler*>("Wrestler*");


    MainWindow w;
    w.show();
    return a.exec();
}
