#include "hexagon.hh"

hexagon::hexagon()
{



}

QRectF hexagon::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                          20 + penWidth, 20 + penWidth);
}


void hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget)
{
        QPointF point1;
        point1.setX( coords_.x() + HEX_WIDTH / 4 );
        point1.setY( coords_.y() - HEX_HEIGHT / 2 );

        QPointF point2;
        point2.setX( coords_.x() - HEX_WIDTH / 4 );
        point2.setY( coords_.y() - HEX_HEIGHT / 2);

        QPointF point3;
        point3.setX( coords_.x() - HEX_WIDTH / 2 );
        point3.setY( coords_.y() );

        QPointF point4;
        point4.setX( coords_.x() - HEX_WIDTH / 4 );
        point4.setY( coords_.y() + HEX_HEIGHT / 2 );

        QPointF point5;
        point5.setX( coords_.x() + HEX_WIDTH / 4 );
        point5.setY( coords_.y() + HEX_HEIGHT / 2 );

        QPointF point6;
        point6.setX( coords_.x() + HEX_WIDTH / 2 );
        point6.setY( coords_.y() );

        QPointF TempHex[6] = {
            point1,
            point2,
            point3,
            point4,
            point5,
            point6
        };

        QBrush brush;
        brush.setColor(Qt::red);
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
        painter->drawPolygon(TempHex, 6);

}

void hexagon::set_coords(QPointF coordinates)
{
    coords_ = coordinates;
}
