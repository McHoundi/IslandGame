#include "gamestate.hh"

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

void GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    phase_ = nextPhase;
}

