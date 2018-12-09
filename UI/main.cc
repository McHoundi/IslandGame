#include "mainwindow.hh"

#include <memory>
#include <QApplication>
#include <QShowEvent>
#include <QMessageBox>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QMessageBox errorbox;
    //errorbox.critical(nullptr, "Error", "Viesti");
    MainWindow w;

    w.show();

    return a.exec();

}
