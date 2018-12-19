#include <cstdlib>

#include "gamemaster.hpp"
#include "battlefield.hpp"

Gamemaster::Gamemaster(int numberEnemiess)
{
    battlefield_.spawnEnemiesRandomLocations(numberEnemiess);
    gameOver_ = false;
    victory_ = false;
    timer_ = 0;
}

void Gamemaster::isGameOvered()
{
    if(battlefield_.isGameOvered() == true)
        gameOver_ = true;
    drawGameOverMessage();
}

void Gamemaster::isVictory()
{
    if(battlefield_.isVictory() == true)
        victory_ = true;
    drawVictoryMessage();
}

void Gamemaster::startGame()
{
    while( !(gameOver_ ^ victory_))//while not happened victory og gameOver
    {
        battlefield_.buttonPress();

        system("clear");

        battlefield_.updatePlayer();
        battlefield_.updateEnemies();
        battlefield_.updateBullets();

        battlefield_.drawBattlefield();

        isVictory();
        isGameOvered();

        timer_++;
    }
}

void Gamemaster::drawGameOverMessage()
{

}

void Gamemaster::drawVictoryMessage()
{

}
