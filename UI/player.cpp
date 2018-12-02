#include "player.hh"


Player::Player(int PlayerID)
{
    id_ = PlayerID;
}

Player::~Player()
{

}

int Player::getPlayerId() const
{
    return id_;
}

void Player::setActionsLeft(unsigned int actionsLeft)
{
    actions_ = actionsLeft;
}

unsigned int Player::getActionsLeft() const
{
    return actions_;
}

void Player::add_pawn(int pawnID)
{
    myPawns_.push_back(pawnID);
}
