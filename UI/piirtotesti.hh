#ifndef PIIRTOTESTI_HH
#define PIIRTOTESTI_HH

#include <QGraphicsItem>


class PiirtoTesti : public QGraphicsItem
{
public:
    Piirtotesti(QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr);
    QRectF boundingRect() const;
};

#endif // PIIRTOTESTI_HH
