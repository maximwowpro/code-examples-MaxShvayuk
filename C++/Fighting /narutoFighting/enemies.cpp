#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "enemies.h"
#include "constants.h"

void Enemy::checkCollisionWithMapAndPlayer(float _dx, float _dy){

    int q = tileSize;
    for (int i = y /q; i <(y + h) /q; i++)
        for (int j = x /q; j <(x + w) /q; j++) {
            if (tileMap[i][j] == '0') {
                if (_dy > 0) { y = i * 32 - h; dy = 0; onGround = true;}
                if (_dy < 0) { y = i * 32 + 32; dy = 0; }
                if (_dx > 0) { x = j * 32 - w; dx = -0.2; }
                if (_dx < 0) { x = j * 32 + 32; dx = 0.2; }
            }
            if(x < 3) { x = 3; dx = -dx; } //щоб не виліз за межі екрану
            if(x > mapW*q - 5 - w/2) { x = mapW*q - 5 - w/2; dx = -dx; }
            if(y < 3) { y = 3; dy = 0; speed = 0; }
            if(y > mapH*q - 15 - h/2) { y = mapH*q - 25 - h/2; dy = -0.6; }
        }
    return;
}

void Enemy::update(float time){
    x += dx*time;
    checkCollisionWithMapAndPlayer(dx, 0);
    y += dy*time;
    checkCollisionWithMapAndPlayer(0, dy);

    if (!isMove) speed = 0;
    if (health <= 0) isAlive = false;

    sprite.setPosition(x + w /2, y + h /2);
    dy += 0.0015*time;
    return;
}


