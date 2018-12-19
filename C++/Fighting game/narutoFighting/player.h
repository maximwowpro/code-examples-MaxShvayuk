#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include <SFML/Graphics.hpp>
#include <map.h>

#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>

#include "animation.h"

using namespace sf;

class Base{
    //base class with main parameters for all other classes
public:

    float x, y, dx, dy, speed, moveTimer, currentFrame;//x,y - coordinates in window; dx,dy - acceleration; currentFrame - variable for animation
    unsigned int health;//w,h-width,height of sprite; x0,y0 - begin point of sprite;
    bool isAlive, isMove, onGround;//isAlive(true = live, false = dead); isMove(true-speed>0; false-speed=0); onGround(true-onGround, false-jump or falling);
    String name;//ID of player/enemy/etc.
    String character;//name of character in Naruto universe
    Texture texture;
    Sprite sprite;
    IntRect mainRect;//rect with coordinates of sprite
    Animation animationManager;
    std::map <std::string, Sound> sounds;//name of sound - sound

    Base(std::string adress, float _x, float _y, int _y0, int _x0, int _w, int _h, std::string _name, std::string _character);

    FloatRect getRect();

    virtual void update(float time) = 0;//absolutelly virtual function

    virtual ~Base(){}
};

class Player : public Base{
public:
    int score;//scores which player had achieved
    Sprite portrait, healthBar, chacraBar;
    int portraitX0, portraitY0, portraitW, portraitH;
    int healthBarX0, healthBarY0, healthBarW, healthBarH;
    int chacraBarX0, chacraBarY0, chacraBarW, chacraBarH;
    IntRect portraitRect, healthBarRect, chacraBarRect;
    Font font;
    Text text;

    enum { left, right, up, down, jump, stay } state;

    Player(std::string adress, float _x, float _y, int _y0, int _x0, int _w, int _h, std::string _name, std::string _character) :
        Base(adress, _x, _y, _y0, _x0, _w, _h, _name, _character)
    {
        portrait.setTexture(texture);
        if(name == "player1") portrait.setPosition(5, 5);
        if(name == "player2") portrait.setPosition(windowW-10-portrait.getTextureRect().width , 10);

        healthBar.setTexture(texture); chacraBar.setTexture(texture);

        score = 0;
        state = stay;
    }

    void setPortrait(int _x0, int _y0, int _w, int _h);

    void setHealthBar(int _x0, int _y0, int _w, int _h);

    void checkCollisionWithMap(float _dx, float _dy);//tileSide - the side of one tile in pixels(for example 32)

    void control();

    void animation(float time, int  number);

    virtual void update(float time);
};
































#endif // PLAYER_H
