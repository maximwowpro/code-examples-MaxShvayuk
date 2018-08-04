#ifndef CHARACTERNARUTO_H
#define CHARACTERNARUTO_H

#include <SFML/Graphics.hpp>

#include "player.h"

class CharacterNaruto : public Player{
    CharacterNaruto(std::string adress, float _x, float _y, int _y0, int _x0, int _w, int _h, std::string _name, std::string _character) :
        Player(adress, _x, _y, _y0, _x0, _w, _h, _name, _character){

    }

    void setPortrait();

    void setHealthBar();

    void checkCollisionWithMap(float _dx, float _dy);//tileSide - the side of one tile in pixels(for example 32)

    void control();

    void animation(float time, int  number);

    virtual void update(float time);
};

























#endif // CHARACTERNARUTO_H

