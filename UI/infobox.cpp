#include "infobox.hh"
#include <QString>
#include <QScrollBar>

infoBox::infoBox()
{


}

void infoBox::printInfo(std::string text) {
    QString string = QString::fromStdString(text);
    append(string);
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());

}
