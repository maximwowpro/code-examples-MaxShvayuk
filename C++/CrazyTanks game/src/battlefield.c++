#include <vector>
#include <string>
#include <list>
#include <iostream>
//#include <chrono>

#include <ctime>
#include <cstdlib>

#include <player.hpp>
#include <enemy.hpp>
#include <bullet.hpp>
#include <battlefield.hpp>

Battlefield::Battlefield()
{
    fillAreaFirstTime();

    button_ = UP;
}

void Battlefield::spawnEnemiesRandomLocations(int numberEnemies)
{
    srand(time(0) );
    enemies_.reserve(numberEnemies);
    for(int i=0; i<numberEnemies; i++)//add enemies to list
        enemies_.push_back(Enemy() );

    int randX = 0;
    int randY = 0;
    for(uint i=0; i<enemies_.size(); i++)
    {
        randX = 1 + rand()%(AREA_X_LINES-1);
        randY = 1 + rand()%(AREA_Y_LINES-6);
        enemies_.at(i).setCoordinates(randX, randY);
    }
}

void Battlefield::fillAreaFirstTime()
{
    char wall = '@';

    area_.reserve(AREA_Y_LINES);
    for(int i=0; i<AREA_Y_LINES; i++)
    {
        area_.push_back(std::string(AREA_X_LINES, ' '));
    }

    *area_.begin()  = std::string(AREA_X_LINES, wall);//top wall
    *(area_.end()-1) = std::string(AREA_X_LINES, wall);//bottom wall


    for(unsigned int i = 0; i<area_.size(); i++)
    {
        area_.at(i).insert(area_.at(i).begin() , wall);//left wall
        area_.at(i).insert(area_.at(i).end() , wall);//right wall
    }

    generateRandomWalls();
}

void Battlefield::generateRandomWalls()
{
    char wall = 'W';
    int numberWalls = 8;//how many wall elements are at battlefield

    srand(time(0));

    for(int i=0 ;i<numberWalls; i++)
    {
        int x = 1 + rand()%(AREA_X_LINES-1);
        int y = 1 + rand()%(AREA_Y_LINES-2);
        area_.at(y)[x] = wall;
    }
}

void Battlefield::drawBattlefield()
{
    for(uint i=0; i<area_.size(); i++)
    {
        for(uint j=0; j<area_.at(i).length(); j++)
        {
            std::cout<<area_.at(i).at(j);
        }
        std::cout<<std::endl;
    }
}

bool Battlefield::checkCoordinatesForPlayerAndEnemy(int x, int y)
{   //return true if position for tank is free
    return (/*area_.at(y).at(x) == ' ' &&*/
            area_.at(y-2).at(x) == ' ' &&
            area_.at(y+2).at(x) == ' ' &&
            area_.at(y).at(x-2) == ' ' &&
            area_.at(y).at(x+2) == ' ' );
}

void Battlefield::addPlayerAndEnemyToArea(int x, int y, std::vector<std::string> tank)
{
    //    std::cout<<"drawPlayer 1"<<std::endl;

    area_.at(y-1).replace(x-1, 3, tank.at(0) );//draw top line of tank
    area_.at(y).  replace(x-1, 3, tank.at(1) );//draw middle line of tank
    area_.at(y+1).replace(x-1, 3, tank.at(2) );//draw down line of tank

    //  std::cout<<"drawPlayer 2"<<std::endl;
}

void Battlefield::updatePlayer()
{
    //    std::cout<<"updatePlayer 1"<<std::endl;

    player_.setDirection(static_cast<Base::direction> (button_) );

    std::vector <std::string> tmp = player_.getImagePlayer();
    player_.setMovingState(true);
    player_.countNextFrameCoordinate();

    int x = player_.getXCoordinate();
    int y = player_.getYCoordinate();

    if(checkCoordinatesForPlayerAndEnemy(x, y)== true)
    {
        std::cout<<"updatePlayer 2   x= "<<x<<"  y = "<<y<<std::endl;
        addPlayerAndEnemyToArea(x, y, tmp);
    }
}

void Battlefield::updateEnemies()
{
    for(uint i=0; i<enemies_.size(); i++)
    {
        std::vector <std::string> tmp = enemies_.at(i).getImageEnemy();
        enemies_.at(i).countNextFrameCoordinate();

        int x = enemies_.at(i).getXCoordinate();
        int y = enemies_.at(i).getYCoordinate();

        if(checkCoordinatesForPlayerAndEnemy(x, y)== true)
        {
            std::cout<<"updateEnemies 2   x= "<<x<<"  y = "<<y<<std::endl;
            addPlayerAndEnemyToArea(x, y, tmp);
        }
    }
}

void Battlefield::updateBullets()
{

}

void Battlefield::buttonPress()
{
    char buttonPress;
    std::cin.get(buttonPress);

    switch(buttonPress)
    {
    case('a'):
        button_ = LEFT;
        break;
    case('d'):
        button_ = RIGHT;
        break;
    case('w'):
        button_ = UP;
        break;
    case('s'):
        button_ = DOWN;
        break;
    case(' '):
        button_ = SPACE;
        break;
    }
}

bool Battlefield::isGameOvered()
{
    if(player_.getLives()==0)
        return true;
    else
        return false;
}

bool Battlefield::isVictory()
{
    if(enemies_.size() == 0)
        return true;
    else
        return false;
}

















