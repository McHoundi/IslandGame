#include "hexagon.hh"
#include "iostream"
#include "QGraphicsScene"

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
        point1.setX( xycoords_.x() + HEX_WIDTH / 4 );
        point1.setY( xycoords_.y() - HEX_HEIGHT / 2 );

        QPointF point2;
        point2.setX( xycoords_.x() - HEX_WIDTH / 4 );
        point2.setY( xycoords_.y() - HEX_HEIGHT / 2);

        QPointF point3;
        point3.setX( xycoords_.x() - HEX_WIDTH / 2 );
        point3.setY( xycoords_.y() );

        QPointF point4;
        point4.setX( xycoords_.x() - HEX_WIDTH / 4 );
        point4.setY( xycoords_.y() + HEX_HEIGHT / 2 );

        QPointF point5;
        point5.setX( xycoords_.x() + HEX_WIDTH / 4 );
        point5.setY( xycoords_.y() + HEX_HEIGHT / 2 );

        QPointF point6;
        point6.setX( xycoords_.x() + HEX_WIDTH / 2 );
        point6.setY( xycoords_.y() );

        QPointF TempHex[6] = {
            point1,
            point2,
            point3,
            point4,
            point5,
            point6
        };

        QBrush brush;
        if ( type_ == "green" ) {
            brush.setColor(Qt::green);
        } else {
            brush.setColor(Qt::red);
        }


        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(brush);
        painter->drawPolygon(TempHex, 6);

}

void hexagon::set_coords(QPointF coordinates)
{
    xycoords_ = coordinates;

}

void hexagon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    type_ = "green";
    QGraphicsScene *current_scene = this->scene();
    current_scene->update();

    std::cout << "Custom item clicked, coords: " << xycoords_.x() << ", " << xycoords_.y() << std::endl;


}
