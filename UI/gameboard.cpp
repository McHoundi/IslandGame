#include "gameboard.hh"
#include "iostream"
GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{
}
/*
virtual void GameBoard::removeTransport(int id) {

}

virtual int GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const{

}
*/

// Luo uuden hexagon olion, laittaa sen kartan sisällä olevaan listaan.
void GameBoard::create_hex(QPointF midpoint, Common::CubeCoordinate cubepoint) {
    new_hex* uus_hex = new new_hex;
    uus_hex->set_coords(midpoint);
    uus_hex->setCoordinates(cubepoint);
    hexes_.push_back(uus_hex);
}

void GameBoard::determine_midpoints()
{
    //Lisätään aluksi origo, eli ensimmäinen layeri

    QPointF midpoint_marker(0,0);
    Common::CubeCoordinate cube_coords;
    Common::CubeCoordinate(0, 0, 0) = cube_coords;

    create_hex(midpoint_marker, cube_coords);


    int layer_counter = 1;


    while ( layer_counter < layer_count_ ) {

        // Siirrytään loopin alussa seuraavaan layeriin, eli ylöspäin, ja aloitetaan piirtäminen siitä.
        layer_counter++;
        midpoint_marker = move_midpoint(midpoint_marker, "N");
        cube_coords.y += 1;
        cube_coords.z -= 1;

        create_hex(midpoint_marker, cube_coords);

        // side_hops on hyppyjen (tai askelten) määrä, mitä tarvitaan päästäksemme jonkin layerin "sivun" päästä päähän.
        // Koska layerin numero on sama kuin sivujen määrä, side_hops on yksi vähemmän kuin layerin numero.
        int side_hops = layer_counter - 1;
        int i;

        //Seuraavat for-loopit liikuttavat keskipiste-merkkiä jokaisen sivun läpi, kiertäen koko layerin.
        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SW");
            cube_coords.x -= 1;
            cube_coords.z += 1;
            create_hex(midpoint_marker, cube_coords);
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "S");
            cube_coords.y -= 1;
            cube_coords.z += 1;
            create_hex(midpoint_marker, cube_coords);
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SE");
            create_hex(midpoint_marker, cube_coords);
            cube_coords.x += 1;
            cube_coords.y -= 1;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NE");
            create_hex(midpoint_marker, cube_coords);
            cube_coords.x += 1;
            cube_coords.z -= 1;

        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "N");
            create_hex(midpoint_marker, cube_coords);
            cube_coords.y += 1;
            cube_coords.z -= 1;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NW");
            cube_coords.y += 1;
            cube_coords.x -= 1;
            //Tarkistetaan, että olemmeko yhden kuvion päässä layerin ylimmästä hexagonista, josta aloitettiin piirtäminen
            if ( i != 1 ) {

                create_hex(midpoint_marker, cube_coords);

            }

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

void GameBoard::addHex(new_hex* newHex) {
    QBrush redbrush;
    redbrush.setColor(Qt::red);
    redbrush.setStyle(Qt::SolidPattern);
    newHex->setBrush(redbrush);
    newHex->scene()->addItem(newHex);
}

void GameBoard::build_map(QGraphicsScene *skene)
{
    /*
    for ( QPointF keskipiste : midpoints_ ) {
        new_hex* uus_hexagon = new new_hex;


        uus_hexagon->set_coords(keskipiste);

        QBrush redbrush;
        redbrush.setColor(Qt::red);
        redbrush.setStyle(Qt::SolidPattern);
        uus_hexagon->setBrush(redbrush);

        skene->addItem(uus_hexagon);


    }
    */


    for ( new_hex* hexi : hexes_ ) {
        addHex(hexi);
    }
}
