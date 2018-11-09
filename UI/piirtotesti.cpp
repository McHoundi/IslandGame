#include "piirtotesti.hh"
#include <QPainter>
#include <QDebug>

PiirtoTesti::PiirtoTesti()

{

}


void PiirtoTesti::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(Qt::black));
    painter->drawEllipse( 0, 0, 10, 10 );
}
