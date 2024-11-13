#include "framework.h"
#include "Player.h"

Player::Player()
{
}

Player::Player(string name, int hp, int atk)
: Creature(name, hp, atk)
{
}
