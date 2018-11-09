#ifndef HEXAGON_HH
#define HEXAGON_HH

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>


class Hexagon : public QGraphicsItem
{

public:
    Hexagon();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


};

#endif // HEXAGON_HH
