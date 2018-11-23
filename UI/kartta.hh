#ifndef KARTTA_HH
#define KARTTA_HH

#include "hexagon.hh"
#include "vector"
#include <QPointF>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QBrush>
#include "mainwindow.hh"
#include "math.h"


const double HEX_SIZE = 20;
const double HEX_WIDTH = 2 * HEX_SIZE;
const double HEX_HEIGHT = sqrt(3) * HEX_SIZE;

class kartta
{
public:
    kartta(); 

    //Määrittää karttapalojen keskipisteiden koordinaatit, ja tallentaa ne vektoriin midpoints_
    void determine_midpoints();

    //determine midpoints()-funktion käyttämä funktio, liikuttelee keskipistettä tarpeen mukaan
    QPointF move_midpoint(QPointF midpoint_marker, std::string direction);

    void build_map(QGraphicsScene* skene);

private:
    std::vector<QPointF> midpoints_;    //Karttapalojen keskipisteet
    //std::vector<hexagon> hexagons_;     //Karttapalat
    int layer_count_ = 11;              //Hexagoni-layerien määrä kartassa.


};

#endif // KARTTA_HH
