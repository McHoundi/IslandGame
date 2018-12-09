#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"
#include "memory"
#include "vector"


class Player : public Common::IPlayer
{
public:

    // Constructor assigns playerID

    Player(int PlayerID);
    ~Player();
    virtual int getPlayerId() const;
    virtual void setActionsLeft(unsigned int actionsLeft);
    virtual unsigned int getActionsLeft() const;

private:
    int actions_; //Actions left
    int id_;    //Player ID

};

#endif // PLAYER_HH
