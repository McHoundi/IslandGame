#include "gameboard.hh"
#include "iostream"
#include  <random>
#include  <iterator>
#include <player.hh>
#include <QObject>
#

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

//seuraavat 2 blokkia alustavat randomgeneraattorin satunnaisen naapurilaatan valitsemiselle


template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}


void GameBoard::determine_midpoints()
{
    //Lisätään aluksi origo, eli ensimmäinen layeri
    double nollakohta = 0;
    QPointF midpoint_marker(nollakohta,nollakohta);
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
        // Koska layerin numero on sama kuin yhdellä sivulla olevien laattojen määrä, side_hops on yksi vähemmän kuin layerin numero.
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


QPointF GameBoard::cube_to_square(Common::CubeCoordinate cubecoords)
{
    return midpoints_.at(cubecoords);
}

std::map<Common::CubeCoordinate, std::shared_ptr<Common::Hex> > GameBoard::get_hexPointers()
{
    return hexPointers_;
}

Common::CubeCoordinate GameBoard::pick_random_available_neighbour(std::shared_ptr<Common::Hex> full_hex)
{
   Common::CubeCoordinate random_neighbour;

    //kerätään naapurilaatoista ei-täydet laatat, ja valitaan niistä satunnainen ja sen koordinaatit.
    std::vector<Common::CubeCoordinate> available_neighbours;
    for ( Common::CubeCoordinate cubecoords : full_hex->getNeighbourVector() ) {
        if ( hexPointers_.at(cubecoords)->getPawnAmount() < 3) {
            if ( cubecoords.x == 0 && cubecoords.y == 0 && cubecoords.z == 0 ) {
                // Do nothing
            } else {
                available_neighbours.push_back(cubecoords);
            }
           }
    }
    random_neighbour = *select_randomly(available_neighbours.begin(), available_neighbours.end());
    return random_neighbour;
}





void GameBoard::set_scene(QGraphicsScene *scene)
{
    scene_ = scene;
}

QGraphicsScene *GameBoard::get_scene()
{
    return scene_;
}

void GameBoard::insert_hexItems(Common::CubeCoordinate cubecoords, hexgraphics* hex)
{
    hexItems_[cubecoords] = hex;

    //alustetaan samalla pawnSlots map
    std::vector<bool> dummy {false, false, false};
    pawnSlots_[cubecoords] = dummy;
}

std::map<Common::CubeCoordinate, hexgraphics *> GameBoard::get_hexItems()
{
    return hexItems_;
}






void GameBoard::removeTransport(int id)
{

}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{

    std::shared_ptr<Common::Hex> hexi = hexPointers_.at(coord);
    hexi->addTransport(transport);

    pixmapgraphics* uusi_transport = new pixmapgraphics;
    QPointF XYCOORDS = cube_to_square(coord);
    std::string tyyppi = transport->getTransportType();
    uusi_transport->setPicture(tyyppi);
    uusi_transport->movePicture(XYCOORDS);
    scene_->addItem(uusi_transport);

}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    Common::CubeCoordinate cubecoords = newHex->getCoordinates();
    hexPointers_[cubecoords] = newHex;

    //Graafinen puoli
    QBrush brush;
    std::string type = newHex->getPieceType();
    if (type == "Peak") {

        brush.setColor(Qt::darkGray);
    } else if (type == "Mountain") {
        brush.setColor(Qt::lightGray);
    } else if (type == "Forest") {
        brush.setColor(Qt::green);
    } else if (type == "Beach") {
        brush.setColor(Qt::yellow);
    } else if (type == "Coral") {
        brush.setColor(Qt::magenta);
    } else if (type == "Water") {
        brush.setColor(Qt::cyan);
    } else {
        std::cout << "Unrecognized type!" << std::endl;
    }

    hexgraphics* HexItem = new hexgraphics;
    brush.setStyle(Qt::SolidPattern);

    HexItem->set_hexptr(newHex);
    HexItem->set_coords(cube_to_square(cubecoords));
    HexItem->setBrush(brush);
    scene_->addItem(HexItem);

    insert_hexItems(cubecoords, HexItem);


}

void GameBoard::removeActor(int actorId)
{

}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{

}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{
    std::shared_ptr<Common::Hex> target_hex = hexPointers_.at(actorCoord);
    // TODO: GRAAFINEN SETTI!
}

void GameBoard::removePawn(int pawnId)
{
    std::shared_ptr<Common::Pawn> pawn = pawns_.at(pawnId);
    Common::CubeCoordinate pawnCoord = pawn->getCoordinates();
    hexPointers_.at(pawnCoord)->removePawn(pawn);
    pawns_.erase(pawnId);

    //Poistetaan pawnin graafinen puoli
    delete pawnItems_.at(pawnId);
    pawnItems_.erase(pawnId);

}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    std::shared_ptr<Common::Pawn> pawn = pawns_.at(pawnId);
    std::shared_ptr<Common::Hex> current_hex = hexPointers_.at(pawn->getCoordinates());
    std::shared_ptr<Common::Hex> target_hex = hexPointers_.at(pawnCoord);
    std::vector<Common::CubeCoordinate> neighbour_tiles = current_hex->getNeighbourVector();

    //A few checks about integrity of this movement before moving

    if ( pawn->getCoordinates() == pawnCoord ) {
        std::cout << "You're already on this tile!" << std::endl;

    } else if ( std::find(neighbour_tiles.begin(), neighbour_tiles.end(), pawnCoord) == neighbour_tiles.end()  ) {
        std::cout << "You're not next to this tile!" << std::endl;
        std::cout << "Your coords: " << pawn->getCoordinates().x << pawn->getCoordinates().y << pawn->getCoordinates().z << std::endl;
    } else if ( hexPointers_.at(pawnCoord)->getPawnAmount() >= 3 ) {
        std::cout << "Tile full!" << std::endl;
    }
    // checks done: can move pawn
    else {
        current_hex->removePawn(pawn);
        target_hex->addPawn(pawn);

        int pawnslot = pawnItems_.at(pawnId)->get_pawnSlot();
        pawnSlots_.at(pawn->getCoordinates()).at(pawnslot-1) = false;

        pawn->setCoordinates(pawnCoord);

        QPointF XYCOORDS = cube_to_square(pawnCoord);
        if ( pawnItems_.find(pawnId) == pawnItems_.end() ) {
            std::cout << "Tätä erroria ei pitäisi tulla" << std::endl;
        } else {
            /* VANHAA MUTTA TOIMIVAA KOODIA
             *
            std::cout << "pawnamount: " << target_hex->getPawnAmount() << std::endl;
            if (target_hex->getPawnAmount() == 1 ) {
                pawnItems_.at(pawnId)->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
            } else if (target_hex->getPawnAmount() == 2 ) {
                pawnItems_.at(pawnId)->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()-HEX_SIZE*0.3,PAWN_WIDTH,PAWN_HEIGHT);
            } else if (target_hex->getPawnAmount() == 3 ) {
                pawnItems_.at(pawnId)->setRect(XYCOORDS.x()-HEX_SIZE*0.3, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
        }
            */

            if ( target_hex->getPawnAmount() == 0 ) {
                pawnItems_.at(pawnId)->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
                pawnSlots_.at(pawnCoord).at(0) = true;
                pawnItems_.at(pawnId)->set_pawnSlot(1);
            } else if ( pawnSlots_.at(pawnCoord).at(0) == false) {
                pawnItems_.at(pawnId)->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
                pawnSlots_.at(pawnCoord).at(0) = true;
                pawnItems_.at(pawnId)->set_pawnSlot(1);
            } else if ( pawnSlots_.at(pawnCoord).at(1) == false ) {
                pawnItems_.at(pawnId)->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()-HEX_SIZE*0.3,PAWN_WIDTH,PAWN_HEIGHT);
                pawnSlots_.at(pawnCoord).at(1) = true;
                pawnItems_.at(pawnId)->set_pawnSlot(2);
            } else if ( pawnSlots_.at(pawnCoord).at(2) == false ) {
                pawnItems_.at(pawnId)->setRect(XYCOORDS.x()-HEX_SIZE*0.3, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
                pawnSlots_.at(pawnCoord).at(2) = true;
                pawnItems_.at(pawnId)->set_pawnSlot(3);
            }

    }

}
}

void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> hexi;
    if ( coord.x == 0 && coord.y == 0 && coord.z == 0 ) {
        Common::CubeCoordinate coords_outside_center = pick_random_available_neighbour(hexPointers_.at(Common::CubeCoordinate(0,0,0)));
        hexi = hexPointers_.at(coords_outside_center);
        coord = coords_outside_center;
    } else {
        hexi = hexPointers_.at(coord);
    }

    std::shared_ptr<Common::Pawn> new_pawn;



    if ( hexi->getPawnAmount() < 3 ) {
        new_pawn = std::make_shared<Common::Pawn>(pawnId, playerId, coord);
    } else {
        Common::CubeCoordinate free_tile_coord = pick_random_available_neighbour(hexi);
        new_pawn = std::make_shared<Common::Pawn>(pawnId, playerId, free_tile_coord);
        hexi = hexPointers_.at(free_tile_coord);
        coord = free_tile_coord;
    }

    hexi->addPawn(new_pawn);
    pawns_[pawnId] = new_pawn;

    // Creating A graphical pawn.

    pawngraphics* uusi_nappula = new pawngraphics;
    //Player player(123);
    QPointF XYCOORDS = cube_to_square(coord);
    int pawnAmount = hexi->getPawnAmount();

    if ( pawnAmount == 0 ) {
        uusi_nappula->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
        pawnSlots_.at(coord).at(0) = true;
        uusi_nappula->set_pawnSlot(1);
    } else if ( pawnSlots_.at(coord).at(0) == false ) {
        uusi_nappula->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
        pawnSlots_.at(coord).at(0) = true;
        uusi_nappula->set_pawnSlot(1);
    } else if ( pawnSlots_.at(coord).at(1) == false ) {
        uusi_nappula->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()-HEX_SIZE*0.3,PAWN_WIDTH,PAWN_HEIGHT);
        pawnSlots_.at(coord).at(1) = true;
        uusi_nappula->set_pawnSlot(2);
    } else if ( pawnSlots_.at(coord).at(2) == false ) {
        uusi_nappula->setRect(XYCOORDS.x()-HEX_SIZE*0.3, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
        pawnSlots_.at(coord).at(2) = true;
        uusi_nappula->set_pawnSlot(3);
    }
    QBrush brush;

    //PELAAJAN VÄRIN HAKU

    brush.setStyle(Qt::SolidPattern);
    if ( new_pawn->getPlayerId() == 1001 ) {
        brush.setColor(Qt::blue);
    } else if ( new_pawn->getPlayerId() == 1002 ) {
        brush.setColor(Qt::red);
    } else if ( new_pawn->getPlayerId() == 1003 ) {
        brush.setColor(Qt::white);
    } else if ( new_pawn->getPlayerId() == 1004 ) {
        brush.setColor(Qt::red);
    }

    uusi_nappula->setBrush(brush);
    scene_->addItem(uusi_nappula);
    pawnItems_[pawnId] = uusi_nappula;
    std::cout << "Pawn added: " << pawnId << " Player ID: " << new_pawn->getPlayerId() << std::endl;

}

//Lähes sama kuin yllä, mutta lisää pawnin aloitusruutuun.
void GameBoard::addPawn(int playerId, int pawnId)
{
    GameBoard::addPawn(playerId, pawnId, Common::CubeCoordinate(0,0,0));


    /*
    std::shared_ptr<Common::Hex> hexi = hexPointers_.at(Common::CubeCoordinate(0,0,0));
    std::shared_ptr<Common::Pawn> new_pawn;

    if ( hexi->getPawnAmount() < 3 ) {
        new_pawn = std::make_shared<Common::Pawn>(pawnId, playerId, Common::CubeCoordinate(0,0,0));
    } else {
        Common::CubeCoordinate free_tile = pick_random_available_neighbour(hexi);
        new_pawn = std::make_shared<Common::Pawn>(pawnId, playerId, free_tile);

    }

    playerPawns_.at(playerId).push_back(pawnId);// LISÄÄ TÄHÄN FIND()-checkki!!


    // Creating A graphical pawn.

    pawngraphics* uusi_nappula = new pawngraphics;
    //Player player(123);
    QPointF XYCOORDS = cube_to_square(coord);
    if ( pawnAmount == 0 ) {
        uusi_nappula->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
    } else if (pawnAmount == 1) {
        uusi_nappula->setRect(XYCOORDS.x()+HEX_SIZE/5, XYCOORDS.y()-HEX_SIZE*0.3,PAWN_WIDTH,PAWN_HEIGHT);
    } else if (pawnAmount == 2) {
        uusi_nappula->setRect(XYCOORDS.x()-HEX_SIZE*0.3, XYCOORDS.y()+HEX_SIZE/5,PAWN_WIDTH,PAWN_HEIGHT);
    }
    QBrush brush;

    //TODO: PELAAJAN VÄRIN HAKU

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    uusi_nappula->setBrush(brush);
    scene_->addItem(uusi_nappula);
    pawnItems_[pawnId] = uusi_nappula;
    hexi->addPawn(new_pawn);
    pawns_[pawnId] = new_pawn;
    */

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
