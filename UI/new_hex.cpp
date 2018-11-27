#include "new_hex.hh"
#include "hexagon.hh"
#include "iostream"
#include "QGraphicsScene"
#include "QVector"

new_hex::new_hex()
{









}


void new_hex::set_coords(QPointF coordinates)
{
    xycoords_ = coordinates;

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

    QVector<QPointF> vektori;
    vektori.append(point1);
    vektori.append(point2);
    vektori.append(point3);
    vektori.append(point4);
    vektori.append(point5);
    vektori.append(point6);

    QPolygonF hexi(vektori);
    this->setPolygon(hexi);

}

void new_hex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QBrush greenbrush;
    greenbrush.setColor(Qt::green);
    greenbrush.setStyle(Qt::SolidPattern);
    this->setBrush(greenbrush);
    //QGraphicsScene *current_scene = this->scene();
    //current_scene->update();

    std::cout << "Custom item clicked, coords: " << xycoords_.x() << ", " << xycoords_.y() << std::endl;


}
