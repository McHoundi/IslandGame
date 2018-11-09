#include "hexagon.hh"

Hexagon::Hexagon()
{

}



QRectF Hexagon::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                          20 + penWidth, 20 + penWidth);
}

static const QPointF points[6] = {
    QPointF(60,0),
    QPointF(29,52),
    QPointF(-29,52),
    QPointF(-60,0),
    QPointF(-29,-52),
    QPointF(29,-52)
};

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

      painter->drawPolygon(points, 6);
}
