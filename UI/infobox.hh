#ifndef INFOBOX_HH
#define INFOBOX_HH


#include <QTextEdit>

class infoBox : public QTextEdit
{
public:
    infoBox();
    void printInfo(std::string text);
};

#endif // INFOBOX_HH
