#ifndef ENEMIES_H
#define ENEMIES_H

#include<SFML/Graphics.hpp>

#include "constants.h"
#include "player.h"

class Enemy : public Base{
public:

    Enemy(std::string adress, float _x, float _y, int _y0, int _x0, int _w, int _h, std::string _name, std::string _character) : Base(adress, _x, _y, _y0, _x0, _w, _h, _name, _character){
        dx = -0.3;
    }

    void checkCollisionWithMapAndPlayer(float _dx, float _dy);//tileSide - the side of one tile in pixels(for example 32)

    void update(float time);
};

























#endif // ENEMIES_H
