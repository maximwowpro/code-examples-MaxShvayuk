#include <vector>
#include <string>
#include <iostream>

#include <player.hpp>

void Player::setImages()
{
    for(int i=0; i<4; i++)
        images_.push_back(std::vector <std::string>() );

    std::vector <std::string> tmp;
    for(int i=0; i<3; i++)
        tmp.push_back(std::string() );

    //LEFT:
    tmp.at(0)= " ==";
    tmp.at(1)= "===";
    tmp.at(2)= " ==";
    images_.at(LEFT) = tmp;

    //RIGHT:
    tmp.at(0)= "== ";
    tmp.at(1)= "===";
    tmp.at(2)= "==";
    images_.at(RIGHT) = tmp;

    //UP:
    tmp.at(0)= " = ";
    tmp.at(1)= "===";
    tmp.at(2)= "===";
    images_.at(UP) = tmp;

    //DOWN:
    tmp.at(0)= "===";
    tmp.at(1)= "===";
    tmp.at(2)= " = ";
    images_.at(DOWN) = tmp;

}

void Player::spawnOnBattlefield()//spawn Player at the middle of the bottom
{
    const int MAX_X_COORDINATE = 79;
    const int MAX_Y_COORDINATE = 19;

    setCoordinates(MAX_X_COORDINATE/2, MAX_Y_COORDINATE-3);
}

std::vector <std::string> Player::getImagePlayer()
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

void Player::setLives(int lives)
{
    lives_ = lives;
}

int Player::getLives()
{
    return lives_;
}

int Player::getScores()
{
    return scores_;
}

void Player::setScores(int scores)
{
    scores_ = scores;
}
