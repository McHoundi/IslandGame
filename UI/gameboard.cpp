#include "gameboard.hh"


GameBoard::GameBoard()
{
    determine_midpoints();
}

GameBoard::~GameBoard()
{
}

void GameBoard::determine_midpoints()
{
    //Lisätään aluksi origo, eli ensimmäinen layeri
    QPointF midpoint_marker(0,0);
    midpoints_.push_back(midpoint_marker);
    int layer_counter = 1;

    while ( layer_counter < layer_count_ ) {

        // Siirrytään loopin alussa seuraavaan layeriin.
        layer_counter++;
        midpoint_marker = move_midpoint(midpoint_marker, "N");

        midpoints_.push_back(midpoint_marker);

        // side_hops on hyppyjen (tai askelten) määrä, mitä tarvitaan päästäksemme jonkin layerin "sivun" päästä päähän.
        // Koska layerin numero on sama kuin sivujen määrä, side_hops on yksi vähemmän kuin layerin numero.
        int side_hops = layer_counter - 1;
        int i;

        //Seuraavat for-loopit liikuttavat keskipiste-merkkiä jokaisen sivun läpi, kiertäen koko layerin.
        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SW");
            midpoints_.push_back(midpoint_marker);
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "S");
            midpoints_.push_back(midpoint_marker);
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SE");
            midpoints_.push_back(midpoint_marker);
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NE");
            midpoints_.push_back(midpoint_marker);
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "N");
            midpoints_.push_back(midpoint_marker);
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NW");
            midpoints_.push_back(midpoint_marker);
        }
    }
}

QPointF GameBoard::move_midpoint(QPointF midpoint_marker, std::string direction)
{
    //Directionit merkataan ilmansuunnilla: North, South, Northwest, jne.
    if (direction == "N") {
        //Tässä miinustetaan, koska y on negatiivinen ylöspäin.
        midpoint_marker.setY( midpoint_marker.y() - HEX_HEIGHT );
    } else if (direction == "S") {
        midpoint_marker.setY( midpoint_marker.y() + HEX_HEIGHT );
    } else if (direction == "SW") {
        midpoint_marker.setX( midpoint_marker.x() - HEX_WIDTH * .75 );
        midpoint_marker.setY( midpoint_marker.y() + HEX_HEIGHT / 2) ;
    } else if (direction == "SE") {
        midpoint_marker.setX( midpoint_marker.x() + HEX_WIDTH * .75 );
        midpoint_marker.setY( midpoint_marker.y() + HEX_HEIGHT / 2) ;
    } else if (direction == "NW") {
        midpoint_marker.setX( midpoint_marker.x() - HEX_WIDTH * .75 );
        midpoint_marker.setY( midpoint_marker.y() - HEX_HEIGHT / 2) ;
    } else if (direction == "NE") {
        midpoint_marker.setX( midpoint_marker.x() + HEX_WIDTH * .75 );
        midpoint_marker.setY( midpoint_marker.y() - HEX_HEIGHT / 2) ;
    }
    return midpoint_marker;
}

void GameBoard::build_map(QGraphicsScene *skene)
{
    for ( QPointF keskipiste : midpoints_ ) {
        hexagon* uus_hexagon = new hexagon;

        uus_hexagon->set_coords(keskipiste);
        skene->addItem(uus_hexagon);
    }
}
