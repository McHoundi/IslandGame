#include "hexgraphics.hh"
#include "iostream"
#include "QGraphicsScene"
#include "QVector"
#include "memory"

hexgraphics::hexgraphics()
{

}


void hexgraphics::set_coords(QPointF coordinates)
{
    xycoords_ = coordinates;

    QPointF point1;
    point1.setX( xycoords_.x() + HEX_WIDTH * 0.25 );
    point1.setY( xycoords_.y() - HEX_HEIGHT * 0.5 );

    QPointF point2;
    point2.setX( xycoords_.x() - HEX_WIDTH * 0.25 );
    point2.setY( xycoords_.y() - HEX_HEIGHT * 0.5 );

    QPointF point3;
    point3.setX( xycoords_.x() - HEX_WIDTH * 0.5 );
    point3.setY( xycoords_.y() );

    QPointF point4;
    point4.setX( xycoords_.x() - HEX_WIDTH * 0.25 );
    point4.setY( xycoords_.y() + HEX_HEIGHT * 0.5  );

    QPointF point5;
    point5.setX( xycoords_.x() + HEX_WIDTH * 0.25 );
    point5.setY( xycoords_.y() + HEX_HEIGHT * 0.5 );

    QPointF point6;
    point6.setX( xycoords_.x() + HEX_WIDTH * 0.5 );
    point6.setY( xycoords_.y() );

    QVector<QPointF> vektori;
    vektori.append(point1);
    vektori.append(point2);
    vektori.append(point3);
    vektori.append(point4);
    vektori.append(point5);
    vektori.append(point6);

    QPolygonF hexi(vektori);
    setPolygon(hexi);

}

void hexgraphics::set_hexptr_coords(Common::CubeCoordinate cubecoords)
{
    hexptr.get()->setCoordinates(cubecoords);
}

std::shared_ptr<Common::Hex> hexgraphics::get_hexptr()
{
    return hexptr;
}

void hexgraphics::set_hexptr(std::shared_ptr<Common::Hex> kuusikulmio_ptr)
{
    hexptr = kuusikulmio_ptr;
}



void hexgraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QBrush greenbrush;
    greenbrush.setColor(Qt::green);
    greenbrush.setStyle(Qt::SolidPattern);
    setBrush(greenbrush);

    emit hexClicked(hexptr);


    /*
    Common::CubeCoordinate cube_coords = this->getCoordinates();



    std::cout << "Custom item clicked, coords: " << xycoords_.x() << ", "
              << xycoords_.y() << "cube : " << cube_coords.x << ", " << cube_coords.y
              << ", " << cube_coords.z << std::endl;
    */
}




/*



shared_ptr<Common::Hex> -> piirrä tän avulla
 *
 *
*/
