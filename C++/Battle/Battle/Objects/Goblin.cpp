#include "framework.h"
#include "Goblin.h"

Goblin::Goblin(string name)
: Monster(name, 50 + rand()% 5, 4 + rand() % 2)
{
}