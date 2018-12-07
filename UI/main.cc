#include "mainwindow.hh"

#include <memory>
#include <QApplication>
#include <QShowEvent>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();

}
