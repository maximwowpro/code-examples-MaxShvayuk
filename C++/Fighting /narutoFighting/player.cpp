#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.h"
#include <string>
#include "map.h"//to have access to tileMap array
#include "animation.h"

using namespace sf;

Base::Base(std::string adress, float _x, float _y, int _x0, int _y0, int _w, int _h, std::string _name, std::string _character){
    x = _x; y = _y; x0 = _x0; y0 = _y0; w = _w; h = _h;
    name = _name; character = _character;
    health = 100;
    isAlive = true; isMove = false; onGround = false;
    dx = 0; dy = 0; speed = 0; moveTimer = 0;
    Image image;
    image.loadFromFile(adress);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(w/2, h/2);//change centre of sprite from left-up angle to centre of image
}

FloatRect Base::getRect(){
    return FloatRect(x, y, w, h);
}

void Player::checkCollisionWithMap(float _dx, float _dy){

    int q = tileSize;//replacement variables for comfort
    for(int i = y/q; i< (y+h)/q; i++)
        for(int j = x/q; j< (x+w)/q; j++){
            if(tileMap[i][j] == '0'){
                if (_dy > 0) { y = i * 32 - h; dy = 0; onGround = true; }
                if (_dy < 0) { y = i * 32 + 32; dy = 0; }
                if (_dx > 0) x = j * 32 - w;
                if (_dx < 0) x = j * 32 + 32;
            }
            if(x < 3) x=3;//щоб не виліз за межі екрану
            if(x > mapW*q - 5 - w/2) x = mapW*q - 5 - w/2;
            if(y < 3) { y = 3; dy = 0; speed = 0; }
            if(y > mapH*q - 15 - h/2) { y = mapH*q - 25 - h/2; dy = -0.6; }
        }
}

void Player::control(){

    if(isAlive){
        if(name == "player1")
        {
            if (Keyboard::isKeyPressed(Keyboard::Left)) { state=left; speed = 0.2; }
            if (Keyboard::isKeyPressed(Keyboard::Right)){ state=right;speed = 0.2; }
            if (Keyboard::isKeyPressed(Keyboard::Up) && onGround) {state = jump; dy = -0.6; onGround = false; }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {state=down; speed=0.1; }
            if (Keyboard::isKeyPressed(Keyboard::Z)) { x = 200; y = 200; }//teleport
        }
        if(name == "player2")
        {
            if (Keyboard::isKeyPressed(Keyboard::A)) { state=left; speed = 0.2; }
            if (Keyboard::isKeyPressed(Keyboard::D)){ state=right;speed = 0.2; }
            if (Keyboard::isKeyPressed(Keyboard::W) && onGround) {state = jump; dy = -0.6; onGround = false; }
            if (Keyboard::isKeyPressed(Keyboard::S)) {state=down; speed=0.1; }
            if (Keyboard::isKeyPressed(Keyboard::Z)) { x = 200; y = 200; }//teleport
        }
    }
}

void Player::animation(float time, int number){
    //number - number № of sprite of animation (for example: 3 of 6 sprites)
    currentFrame += 0.005*time;
    if(currentFrame > (float)number) currentFrame -= float(number);
    //animationManager.setAnimationSprite(texture, );


}

void Player::update(float time){

    control();
    switch(state){
    case left:dx = -speed; break;
    case right:dx = speed; break;
    case up:break;
    case down:/*dy = speed;*/break;
    case jump:break;
    case stay:break;
    }

    x += dx*time;
    checkCollisionWithMap(dx, 0);
    y += dy*time;
    checkCollisionWithMap(0, dy);
    //if(isAlive) setPlayerCoordinateForView(x, y);
    if (!isMove) speed = 0;

    healthBar.setTextureRect(IntRect(healthY0, healthX0, healthW/100*health, healthH));

    sprite.setPosition(x + w/2, y + h/2 );

    if (health<=0) isAlive = false;

    dy += 0.0015*time;
}

void Player::setPortrait(int _x0, int _y0, int _w, int _h){

    portrait.setTextureRect(IntRect(_y0, _x0, _w, _h));
//    if(name == "player1") portrait.setPosition(5, 5);
//    if(name == "player2") portrait.setPosition(windowW-10-_w, 10);
    return;
}

void Player::setHealthBar(int _x0, int _y0, int _w, int _h){

    healthX0 = _x0; healthY0 = _y0; healthW = _w; healthH = _h;
    healthBar.setTexture(texture);
    healthBar.setTextureRect(IntRect(_y0, _x0, _w, _h));
    if(name == "player1") healthBar.setPosition(150, 100);
    if(name == "player2") healthBar.setPosition(windowW-10-_w-150, 100);
    return;
}













