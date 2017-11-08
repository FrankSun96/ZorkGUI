#include "enemy.h"

Enemy::Enemy(int health, int strength, string pic, bool isBoss)
{
    this->health = health;
    this->strength = strength;
    this->pic = pic;
    this->isBoss = isBoss;
}

int Enemy::getHealth()
{
    return health;
}

int Enemy::getStrength()
{
    return strength;
}

string Enemy::getPic()
{
    return pic;
}

bool Enemy::returnBoss()
{
    return isBoss;
}
