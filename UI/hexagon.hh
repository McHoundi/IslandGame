#ifndef HEXAGON_HH
#define HEXAGON_HH



#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QBrush>

#include "string"
#include "vector"
#include "math.h"

#include "actor.hh"
#include "transport.hh"
#include "pawn.hh"

class hexagon : public QGraphicsItem
{
public:
    hexagon();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override; // Piirtää yksittäisen hexagonin kartalle
    void set_coords(QPointF coordinates);

private:
    QPointF coords_;        // Keskipisteen koordinaatit
    std::string type_;      // Karttapalan tyyppi
    std::string hidden_;    // Karttapalan "pohjassa" oleva toimija
    std::vector<Common::Actor> actors_;         // Karttapalassa olevat NPC:t
    std::vector<Common::Transport> transports_; // Karttapalassa olevat transport toimijat
    std::vector<Common::Pawn> pawns_;           // Karttapalassa olevat pelinappulat

    const double HEX_SIZE = 20;
    const double HEX_WIDTH = 2 * HEX_SIZE;
    const double HEX_HEIGHT = sqrt(3) * HEX_SIZE;
};


#endif // HEXAGON_HH
