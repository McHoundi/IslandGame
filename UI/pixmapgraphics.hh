#ifndef PIXMAPGRAPHICS_HH
#define PIXMAPGRAPHICS_HH

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


class pixmapgraphics : public QGraphicsPixmapItem
{
public:
    pixmapgraphics();
    // asettaa itemille pixmapin annetun tyypin perusteella
    void setPicture(std::string type);
    // muuttaa itemin paikkaa annetun koordinaatin hexiin
    void movePicture(QPointF coords);
};

#endif // PIXMAPGRAPHICS_HH
