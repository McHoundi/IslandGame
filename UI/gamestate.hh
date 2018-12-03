#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"
#include "gameboard.hh"

class GameState : public Common::IGameState
{
public:
    GameState();
    ~GameState();
    virtual Common::GamePhase currentGamePhase() const;
    virtual int currentPlayer() const;
    virtual void changeGamePhase(Common::GamePhase nextPhase);
    virtual void changePlayerTurn(int nextPlayer);
    void set_boardPTR(std::shared_ptr<Student::GameBoard> ptr);
    void run_phase();

public slots:
    void hex_chosen(std::shared_ptr<Common::Hex> hexi);

private:
    Common::GamePhase phase_ = Common::GamePhase::MOVEMENT; //current GamePhase
    int player_; //Current player's ID
    std::shared_ptr<Student::GameBoard> boardPTR_;

};

#endif // GAMESTATE_HH
