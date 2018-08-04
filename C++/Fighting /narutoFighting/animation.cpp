#include<SFML/Graphics.hpp>

#include "animation.h"

using namespace sf;

Animation::Animation(){ rect.left = 0; rect.top = 0; rect.width = 0; rect.height = 0; }

void Animation::setAnimationSprite(Texture& _texture, int _x0, int _y0, int _w, int _h, int _number, bool _isLeft){

    if(!_isLeft) { rect.left = (_x0 + _w*_number); rect.top = _y0; rect.width = _w; rect.height = _h; }//if dont need flipped sprite
    else         { rect.left = (_x0 + _w*_number + _w); rect.top = _y0; rect.width = -_w; rect.height = _h; }//if we need flipped sprite

    sprite.setTexture(_texture);
    sprite.setTextureRect(rect);
}

Sprite Animation::getAnimationSprite(){
    return sprite;
}

