#include "gameboard.hh"
#include "iostream"

namespace Student {

GameBoard::GameBoard()
{
    determine_midpoints();

    //seuraava for-loop alustaa hexPointers-mapin, johon asetetaan addHexin yhteydessä pointereita.
    for ( auto const& it : midpoints_ ) {
        hexPointers_.insert(std::pair<Common::CubeCoordinate, std::shared_ptr<Common::Hex>>(it.first, nullptr) );
    }

}

GameBoard::~GameBoard()
{

}


// Luo uuden hexagon olion, laittaa sen kartan sisällä olevaan listaan.


void GameBoard::determine_midpoints()
{
    //Lisätään aluksi origo, eli ensimmäinen layeri

    QPointF midpoint_marker(0,0);
    Common::CubeCoordinate cube_coords;
    Common::CubeCoordinate(0, 0, 0) = cube_coords;

    midpoints_[cube_coords] = midpoint_marker;


    int layer_counter = 1;


    while ( layer_counter < layerCount_ ) {

        // Siirrytään loopin alussa seuraavaan layeriin, eli ylöspäin, ja aloitetaan piirtäminen siitä.
        layer_counter++;
        midpoint_marker = move_midpoint(midpoint_marker, "N");
        cube_coords.y += 1;
        cube_coords.z -= 1;
        midpoints_[cube_coords] = midpoint_marker;

        // side_hops on hyppyjen (tai askelten) määrä, mitä tarvitaan päästäksemme jonkin layerin "sivun" päästä päähän.
        // Koska layerin numero on sama kuin sivujen määrä, side_hops on yksi vähemmän kuin layerin numero.
        int side_hops = layer_counter - 1;
        int i;

        //Seuraavat for-loopit liikuttavat keskipiste-merkkiä jokaisen sivun läpi, kiertäen koko layerin.
        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SW");
            cube_coords.x -= 1;
            cube_coords.z += 1;
            midpoints_[cube_coords] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "S");
            cube_coords.y -= 1;
            cube_coords.z += 1;
            midpoints_[cube_coords] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "SE");
            cube_coords.x += 1;
            cube_coords.y -= 1;
            midpoints_[cube_coords] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NE");
            cube_coords.x += 1;
            cube_coords.z -= 1;
            midpoints_[cube_coords] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "N");
            cube_coords.y += 1;
            cube_coords.z -= 1;
            midpoints_[cube_coords] = midpoint_marker;
        }

        for ( i = side_hops; i != 0; i-- ) {
            midpoint_marker = move_midpoint(midpoint_marker, "NW");
            cube_coords.y += 1;
            cube_coords.x -= 1;
            //Tarkistetaan, että olemmeko yhden kuvion päässä layerin ylimmästä hexagonista, josta aloitettiin piirtäminen
            if ( i != 1 ) {
                midpoints_[cube_coords] = midpoint_marker;
            }
        }
    }





}

QPointF GameBoard::move_midpoint(QPointF midpoint_marker, std::string direction)
{
    //Directionit merkataan ilmansuunnilla: North, South, Northwest, jne.
	/* Keskipisteiden siirto laskettu niin, että ylä- ja alapuolella sijaitseviin keskipisteisiin on 
	 * matkaa kuusikulmion korkeuden (HEX_HEIGHT) verran, ja sivulla sijaitseviin
	 * keskipisteisiin 3/4 kuusikulmion leveydestä (HEX_WIDTH) sivusuuntaan, ja 
	 * puoli korkeutta pystysuoraan suuntaan.
	 */
	
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

/*
void GameBoard::addHex(hexgraphics* newHex) {
    QBrush redbrush;
    redbrush.setColor(Qt::red);
    redbrush.setStyle(Qt::SolidPattern);
    newHex->setBrush(redbrush);
    newHex->scene()->addItem(newHex);
}
*/



QPointF GameBoard::cube_to_square(Common::CubeCoordinate cubecoords)
{
    for (auto const& it : midpoints_ ) {
        if ( it.first == cubecoords ){
            return it.second;
        }
    }
}

std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex> > GameBoard::get_hexPointers()
{
    return hexPointers_;
}






void GameBoard::removeTransport(int id)
{

}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{

}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{

    Common::CubeCoordinate cubecoords = newHex->getCoordinates();
    //std::cout << newHex->getPieceType() << std::endl;
    hexPointers_[cubecoords] = newHex;


}

void GameBoard::removeActor(int actorId)
{

}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{

}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{

}

void GameBoard::removePawn(int pawnId)
{

}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{

}

void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{

}

void GameBoard::addPawn(int playerId, int pawnId)
{

}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{

    if ( hexPointers_.find(hexCoord) == hexPointers_.end()) {
        return nullptr;
    }
    return hexPointers_.at(hexCoord);

}

bool GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{
    if ( hexPointers_.at(tileCoord)->getPieceType() == "Water" ) {
        return true;
    } else {
        return false;
    }
}

int GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{
    if ( hexPointers_.find(tileCoord) == hexPointers_.end()) {
        return -1;
    } else {
        return hexPointers_.at(tileCoord)->getPawnAmount();
    }
}

}
