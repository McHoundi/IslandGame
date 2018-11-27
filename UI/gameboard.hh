#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>

#include "new_hex.hh"
#include "igameboard.hh"
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

class GameBoard //: public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();
    //Määrittää karttapalojen keskipisteiden koordinaatit, ja tallentaa ne vektoriin midpoints_
    void determine_midpoints();

    //determine midpoints()-funktion käyttämä funktio, liikuttelee keskipistettä tarpeen mukaan
    QPointF move_midpoint(QPointF midpoint_marker, std::string direction);

    //void addHex(hexagon newHex);

    //Alustaa ja piirtää kartan
    void build_map(QGraphicsScene* skene);

private:
    std::vector<QPointF> midpoints_;    //Karttapalojen keskipisteet
    //std::vector<hexagon> hexagons_;     //Karttapalat
    int layer_count_ = 11;              //Hexagoni-layerien määrä kartassa.
};
#endif // GAMEBOARD_HH
