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
#include "math.h"

const double HEX_SIZE = 20;
const double HEX_WIDTH = 2 * HEX_SIZE;
const double HEX_HEIGHT = sqrt(3) * HEX_SIZE;

namespace Student {

class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();
    //Määrittää karttapalojen keskipisteiden koordinaatit, ja tallentaa ne vektoriin midpoints_
    void determine_midpoints();

    //determine midpoints()-funktion käyttämä funktio, liikuttelee keskipistettä tarpeen mukaan
    QPointF move_midpoint(QPointF midpoint_marker, std::string direction);

    //Alustaa ja piirtää kartan
    void build_map(QGraphicsScene* skene);

    QPointF cube_to_square(Common::CubeCoordinate cubecoords);


    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> get_hexPointers();

    virtual int checkTileOccupation(Common::CubeCoordinate tileCoord) const;
    virtual bool isWaterTile(Common::CubeCoordinate tileCoord) const;
    virtual std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const;
    virtual void addPawn(int playerId, int pawnId);
    virtual void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord);
    virtual void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);
    virtual void removePawn(int pawnId);
    virtual void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord);
    virtual void moveActor(int actorId, Common::CubeCoordinate actorCoord);
    virtual void removeActor(int actorId);
    virtual void addHex(std::shared_ptr<Common::Hex> newHex);
    virtual void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord);
    virtual void moveTransport(int id, Common::CubeCoordinate coord);
    virtual void removeTransport(int id);


private:
    int layer_count_ = 11;              //Hexagoni-layerien määrä kartassa.
    std::map<Common::CubeCoordinate, QPointF> midpoints_; //Hexagonien keskipisteet CubeCoordinate ja xy-muodoissa
    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexPointers_;
    std::vector<new_hex*> hexes_;
};

}
#endif // GAMEBOARD_HH
