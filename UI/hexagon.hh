#ifndef HEXAGON_HH
#define HEXAGON_HH

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <string>


class Hexagon : public QGraphicsItem
{

public:
    Hexagon();
    struct TempStruct
    {
        QPointF keskipiste_array[1000];
    };
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPointF move_midpoint(QPointF midpoint_marker, std::string direction);
    void draw_map();
    TempStruct determine_midpoints(TempStruct midpoint_vessel, int hexagon_amount);

};

#endif // HEXAGON_HH
