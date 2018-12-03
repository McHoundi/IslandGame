#ifndef PAWNGRAPHICS_HH
#define PAWNGRAPHICS_HH

#include "hex.hh"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPointF>
#include "string"
#include "vector"
#include "math.h"
#include "pawn.hh"
#include "hexgraphics.hh"

const double PAWN_WIDTH = 0.4*HEX_SIZE;
const double PAWN_HEIGHT = 0.4*HEX_SIZE;

class pawngraphics : public QGraphicsEllipseItem
{
public:
    pawngraphics();
    void set_coords(QPointF coordinates);

private:
    QPointF xycoords_;
};

#endif // PAWNGRAPHICS_HH
