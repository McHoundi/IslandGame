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
    void set_pawnSlot(int slot);
    int get_pawnSlot();

private:
    QPointF xycoords_;
    int pawnSlot_; //pawnSlot pitää kirjaa siitä, missä kolmesta yksittäisen hexin sisällä graafisesta "slotissa" eli sijainnissa pawni sijaitsee.
};

#endif // PAWNGRAPHICS_HH
