#include "gamestate.hh"
#include "iostream"

GameState::GameState()
{
    player_ = 1001; //Player 1 always starts
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

