#include "player.hh"


Player::Player()
{

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
