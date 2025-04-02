#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont defaultFont("Arial", 10);
    a.setFont(defaultFont);

    qRegisterMetaType<Wrestler*>("Wrestler*");


    MainWindow w;
    w.show();
    return a.exec();
}
