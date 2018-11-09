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

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
      painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}