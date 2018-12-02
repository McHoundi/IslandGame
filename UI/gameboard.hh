#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>

#include "hexgraphics.hh"
#include "igameboard.hh"
#include "vector"
#include <QPointF>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QBrush>
#include "math.h"
#include "player.hh"


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

    QPointF cube_to_square(Common::CubeCoordinate cubecoords);

    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> get_hexPointers();

    // Valitsee satunnaisen naapurihexin, käytetään jos pawneja on liikaa.
    Common::CubeCoordinate pick_random_available_neighbour(std::shared_ptr<Common::Hex> hexi);

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
    int layerCount_ = 20;              //Hexagoni-layerien määrä kartassa.
    std::map<Common::CubeCoordinate, QPointF> midpoints_; //Hexagonien keskipisteet CubeCoordinate ja xy-muodoissa
    std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex>> hexPointers_;
    std::vector<hexgraphics*> hexes_;
    std::map<int, std::shared_ptr<Common::Pawn>> pawns_;
    std::vector<Player> players_;
};

}
#endif // GAMEBOARD_HH
