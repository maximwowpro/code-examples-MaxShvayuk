#include "background.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;

void setBackgound(RenderWindow& window, std::string adress, int x0, int y0, int w, int h){
    //&window - link to window, adress - adress to your image x0, y0 - start points at the image
    // w - width, h - height
    Image image;
    image.loadFromFile(adress);
    Texture backgroundTexture;
    backgroundTexture.loadFromImage(image);
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(IntRect(x0, y0, w, h) );
    window.draw(backgroundSprite);
    return;
}


