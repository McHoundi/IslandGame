#ifndef NEW_HEX_HH
#define NEW_HEX_HH


//HEXAGONIN TESTAUS
#include "hex.hh"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPainter>
#include <QPointF>
#include <QBrush>

#include "string"
#include "vector"
#include "math.h"

#include "actor.hh"
#include "transport.hh"
#include "pawn.hh"

class new_hex : public QGraphicsPolygonItem
{
public:
    new_hex();
    void set_coords(QPointF coordinates);
    void set_hexptr_coords(Common::CubeCoordinate cubecoords);
    std::shared_ptr<Common::Hex> get_hexptr();
    void set_hexptr(std::shared_ptr<Common::Hex> kuusikulmio_ptr);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:
    std::shared_ptr<Common::Hex> hexptr = nullptr;    //Osoitin tämän Polygonitemin esittämään hexiin.
    QPointF xycoords_;        // Keskipisteen koordinaatit (muodossa x,y)

    const double HEX_SIZE = 20;
    const double HEX_WIDTH = 2 * HEX_SIZE;
    const double HEX_HEIGHT = sqrt(3) * HEX_SIZE;

};


#endif // HEXAGON_HH
