#include <string>

#include <bullet.hpp>

std::string Bullet::getImageBullet()
{
    return image_;
}

void Bullet::setIsPlayers(bool newOwner)//set isPlayers_
{
    isPlayers_ = newOwner;
}

bool Bullet::getIsPlayers()//get isPlayers_ variable
{
    return isPlayers_;
}
