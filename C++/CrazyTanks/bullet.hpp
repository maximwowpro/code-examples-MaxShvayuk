#ifndef BULLET_HPP
#define BULLET_HPP

#include <string>

#include <base.hpp>

class Bullet:public Base
{
private:
    bool isPlayers_;//if bullet was shooted by Player = true, if by Enemy = false
    std::string image_;
public:
    Bullet(bool isPlayers):Base()
    {
        isPlayers_ = isPlayers;
        image_ = "O";
    }
    std::string getImageBullet();
    void setIsPlayers(bool newOwner);//set isPlayers_
    bool getIsPlayers();//get isPlayers_ variable
    ~Bullet(){}
};

#endif // BULLET_HPP

