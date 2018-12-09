#include "mainwindow.hh"
#include "ioexception.hh"
#include "formatexception.hh"
#include <memory>
#include <QApplication>
#include <QShowEvent>
#include <QMessageBox>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QMessageBox errorbox;
    //
    MainWindow w;
    try {
        w.initialize_runner();
    } catch ( Common::FormatException error ) {
       errorbox.critical(nullptr, "FormatException! Closing program.", QString::fromStdString(error.msg()));
       return -1;
    } catch ( Common::IoException error ) {
        errorbox.critical(nullptr, "IOException! Closing program.", QString::fromStdString(error.msg()));
        return -1;
    }

    w.show();

    return a.exec();

}
