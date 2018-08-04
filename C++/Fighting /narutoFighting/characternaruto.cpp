#include<SFML/Graphics.hpp>

#include "characternaruto.h"
#include "player.h"
#include "constants.h"

using namespace sf;

void CharacterNaruto::setPortrait(){
    int _x0 =   5;
    int _y0 = 280;
    int _w  = 130;
    int _h  = 150;
    portrait.setTexture(texture);
    portrait.setTextureRect(IntRect(_y0, _x0, _w, _h));
    if(name == "player1") portrait.setPosition(5, 5);
    if(name == "player2") portrait.setPosition(windowW-10-_w, 10);
    return;
}

//void  CharacterNaruto::setHealthBar(){

//    int _x0 = 321; int _y0 = 5536; int _w = 300; int _h = 22;

//    healthBar.setTexture(texture);
//    healthBar.setTextureRect(IntRect(_x0, _y0, _w, _h));
//    if(name == "player1") healthBar.setPosition(150, 100);
//    if(name == "player2") healthBar.setPosition(windowW-10-_w-150, 100);
//    return;
//}

