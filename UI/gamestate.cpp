#include "gamestate.hh"
#include "iostream"
#include "algorithm"

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


    if (std::find(availablePlayers_.begin(), availablePlayers_.end(), nextPlayer) != availablePlayers_.end() ) {
        player_ = nextPlayer;
    }

}

void GameState::addPlayer(int playerID)
{
    availablePlayers_.push_back(playerID);
}

void GameState::removePlayer(int playerID)
{
    availablePlayers_.erase(std::remove(availablePlayers_.begin(), availablePlayers_.end(), playerID), availablePlayers_.end());
}

bool GameState::isAnyoneAlive(){
    if ( availablePlayers_.size() > 1) {
        return true;
    } else {
        return false;
    }
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

