#ifndef WHEEL_HH
#define WHEEL_HH

#include "QGraphicsPixmapItem"
#include "vector"


class wheel : public QGraphicsPixmapItem
{
public:
    wheel();
    void setPicture(std::pair<std::string, std::string> pari);
    std::vector<QPixmap> get_pixmaps();

private:
    std::vector<QPixmap> pixmaps_;
};


#endif // WHEEL_HH
