#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"


class Player : public Common::IPlayer
{
public:
	// Constructor assigns playerID and basePawnID.
    Player(int PlayerID);
    ~Player();
    virtual int getPlayerId() const;
    virtual void setActionsLeft(unsigned int actionsLeft);
    virtual unsigned int getActionsLeft() const;

private:
    int actions_; //Actions left
    int id_;    //Player ID (1001, 1002, 1003 tai 1004)
	int basePawnID_; // Pawnien ID pohja, määräytyy pelaajaID:n mukaan.
	std::vector<Common::Pawn> pawns_;
};

#endif // PLAYER_HH
