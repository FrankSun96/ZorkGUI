#ifndef ENEMY_H
#define ENEMY_H
#include <string>
using namespace std;
class Enemy{
public:
    Enemy(int health, int strength, string pic, bool isBoss);
    int getHealth();
    int getStrength();
    string getPic();
    bool returnBoss();
private:
    int health;
    int strength;
    bool isBoss;
    string pic;
};

#endif // ENEMY_H
