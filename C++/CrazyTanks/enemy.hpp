#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include <vector>

#include <base.hpp>

class Enemy:public Base
{
private:
    std::vector < std::vector <std::string> > images_;
    void spawnInRandomCoordinates();//for creating an Enemy at random place on the Battlefield, use only in constructor
    void setImages();//use ONLY in constructor
public:
    Enemy():Base()
    {
        setImages();
        spawnInRandomCoordinates();        
    }
    void randomAction();//later
    std::vector <std::string> getImageEnemy();
    ~Enemy(){}
};

#endif // ENEMY_HPP

