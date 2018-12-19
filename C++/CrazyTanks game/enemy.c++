#include <string>
#include <vector>

#include <cstdlib>
#include <ctime>

#include <enemy.hpp>

void Enemy::spawnInRandomCoordinates()
{
    const int MAX_X_COORDINATE = 79;
    const int MAX_Y_COORDINATE = 19;

    srand(time(0));

    int randX = 2 + (rand() % (MAX_X_COORDINATE-4));
    int randY = 2 + (rand() % (MAX_Y_COORDINATE-4));

    setCoordinates(randX, randY);
}

void Enemy::setImages()
{
    for(int i=0; i<4; i++)
        images_.push_back(std::vector <std::string>() );

    std::vector <std::string> tmp;
    for(int i=0; i<3; i++)
        tmp.push_back(std::string() );

    //LEFT:
    tmp.at(0)= " **";
    tmp.at(1)= "***";
    tmp.at(2)= " **";
    images_.at(LEFT) = tmp;

    //RIGHT:
    tmp.at(0)= "** ";
    tmp.at(1)= "***";
    tmp.at(2)= "** ";
    images_.at(RIGHT) = tmp;

    //UP:
    tmp.at(0)= " * ";
    tmp.at(1)= "***";
    tmp.at(2)= "***";
    images_.at(UP) = tmp;

    //DOWN:
    tmp.at(0)= "***";
    tmp.at(1)= "***";
    tmp.at(2)= " * ";
    images_.at(DOWN) = tmp;

}

void Enemy::randomAction()//later
{

}

std::vector <std::string> Enemy::getImageEnemy()
{
    switch(direction_)
    {
    case(LEFT):
        return images_.at(LEFT);

    case(RIGHT):
        return images_.at(RIGHT);

    case(UP):
        return images_.at(UP);

    case(DOWN):
        return images_.at(DOWN);
    }    
}






















