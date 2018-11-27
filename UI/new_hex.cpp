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
    Common::CubeCoordinate cube_coords = this->getCoordinates();



    std::cout << "Custom item clicked, coords: " << xycoords_.x() << ", "
              << xycoords_.y() << "cube : " << cube_coords.x << ", " << cube_coords.y
              << ", " << cube_coords.z << std::endl;

}

/*

An interface is a programming structure/syntax that allows the computer to enforce certain properties on an object (class). For example, say we have a car class and a scooter class and a truck class. Each of these three classes should have a start_engine() action. How the "engine is started" for each vehicle is left to each particular class, but the fact that they must have a start_engine action is the domain of the interface.


shared_ptr<Common::Hex> -> piirrä tän avulla
 *
 * /
