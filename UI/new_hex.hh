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

class new_hex : public QGraphicsPolygonItem, public Common::Hex
{
public:
    new_hex();
    void set_coords(QPointF coordinates);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:
    QPointF xycoords_;        // Keskipisteen koordinaatit (muodossa x,y)
    std::string type_;      // Karttapalan tyyppi
    std::string hidden_;    // Karttapalan "pohjassa" oleva toimija

    const double HEX_SIZE = 20;
    const double HEX_WIDTH = 2 * HEX_SIZE;
    const double HEX_HEIGHT = sqrt(3) * HEX_SIZE;

};


#endif // HEXAGON_HH
