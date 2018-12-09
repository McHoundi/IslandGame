#include "gamestate.hh"
#include "iostream"
#include "algorithm"

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


    if (std::find(availablePlayers_.begin(), availablePlayers_.end(), nextPlayer) != availablePlayers_.end() ) {
        player_ = nextPlayer;
    }

}

void GameState::addPlayer(int playerID)
{
    availablePlayers_.push_back(playerID);
}


void GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    if ( currentGamePhase() == Common::GamePhase::MOVEMENT  && nextPhase == Common::GamePhase::SINKING ){
        phase_ = nextPhase;
    } else if ( currentGamePhase() == Common::GamePhase::SINKING && nextPhase == Common::GamePhase::SPINNING ){
        phase_ = nextPhase;
    } else if ( currentGamePhase() == Common::GamePhase::SPINNING && nextPhase == Common::GamePhase::MOVEMENT ) {
        phase_ = nextPhase;
    }

}

