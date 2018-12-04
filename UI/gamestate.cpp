#include "gamestate.hh"
#include "iostream"

GameState::GameState()
{

}

GameState::~GameState()
{

}

Common::GamePhase GameState::currentGamePhase() const
{
    return phase_;
}

int GameState::currentPlayer() const
{
    return player_;
}

void GameState::changePlayerTurn(int nextPlayer)
{
    player_ = nextPlayer;
}

void GameState::set_boardPTR(std::shared_ptr<Student::GameBoard> ptr)
{
    boardPTR_ = ptr;
}

void GameState::run_phase()
{
    hexgraphics* hexItem = new hexgraphics;
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    hexItem->set_coords(boardPTR_->cube_to_square(Common::CubeCoordinate(0,0,0)));
    hexItem->setBrush(brush);
    boardPTR_->get_scene()->addItem(hexItem);


    QObject::connect(hexItem, &hexgraphics::hexClicked, this, &GameState::hex_chosen);

}

void GameState::hex_chosen(std::shared_ptr<Common::Hex> hexi)
{
    std::cout << "signal läpi. hex coordinates: " << hexi->getCoordinates().x << " " << hexi->getCoordinates().y << " " << hexi->getCoordinates().z << std::endl;
}

void GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    phase_ = nextPhase;
}

