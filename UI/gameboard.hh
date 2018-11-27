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

class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();
    //Määrittää karttapalojen keskipisteiden koordinaatit, ja tallentaa ne vektoriin midpoints_
    void determine_midpoints();

    void create_hex(QPointF midpoint, Common::CubeCoordinate cubepoint);

    //determine midpoints()-funktion käyttämä funktio, liikuttelee keskipistettä tarpeen mukaan
    QPointF move_midpoint(QPointF midpoint_marker, std::string direction);

    //Alustaa ja piirtää kartan
    void build_map(QGraphicsScene* skene);


private:
    int layer_count_ = 4;              //Hexagoni-layerien määrä kartassa.
    std::vector<new_hex*> hexes_;
};
#endif // GAMEBOARD_HH
