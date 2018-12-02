#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"
#include "memory"
#include "vector"
#include "pawn.hh"


class Player : public Common::IPlayer
{
public:
    Player(int PlayerID);
    ~Player();
    virtual int getPlayerId() const;
    virtual void setActionsLeft(unsigned int actionsLeft);
    virtual unsigned int getActionsLeft() const;

private:
    int actions_; //Actions left
    int id_;    //Player ID
    std::vector<std::shared_ptr<Common::Pawn>> pawns_; //The pawns owned by player
};

#endif // PLAYER_HH
