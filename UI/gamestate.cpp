#include "gamestate.hh"
#include "iostream"
#include "algorithm"

GameState::GameState()
{
    phase_ = Common::GamePhase::MOVEMENT;
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

std::vector<int> GameState::get_availablePlayers()
{
    return availablePlayers_;
}

void GameState::addPlayer(int playerID)
{
    availablePlayers_.push_back(playerID);

}

void GameState::set_infobox(infoBox* boxi) {
    infobox_ = boxi;
}

void GameState::removePlayer(int playerID)
{
    availablePlayers_.erase(std::remove(availablePlayers_.begin(), availablePlayers_.end(), playerID), availablePlayers_.end());
}

bool GameState::isAnyoneAlive(){
    //Checks whether there are more than one players left.
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
        if ( infobox_ != nullptr ) {
            infobox_->printInfo("Gamephase changed to SINKING");
        }

    } else if ( currentGamePhase() == Common::GamePhase::SINKING && nextPhase == Common::GamePhase::SPINNING ){
        phase_ = nextPhase;
        if ( infobox_ != nullptr ) {
            infobox_->printInfo("Gamephase changed to SPINNING");
        }
    } else if ( currentGamePhase() == Common::GamePhase::SPINNING && nextPhase == Common::GamePhase::MOVEMENT ) {
        phase_ = nextPhase;
        if ( infobox_ != nullptr ) {
            infobox_->printInfo("Gamephase changed to MOVEMENT");
        }
    }


}

