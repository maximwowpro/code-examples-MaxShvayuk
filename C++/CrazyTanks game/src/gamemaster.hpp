#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP


#include "battlefield.hpp"

class Gamemaster
{
public:
    Battlefield battlefield_;
    bool gameOver_;
    bool victory_;
    int timer_;
    void isGameOvered();
    void isVictory();
    void drawGameOverMessage();
    void drawVictoryMessage();
    void updateBattlefield();
public:
    Gamemaster(int numberEnemiess);
    void startGame();
};

























#endif // GAMEMASTER_HPP

