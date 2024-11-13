#include "framework.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(string name, int hp, int atk)
: Creature(name, hp, atk)
{
}
