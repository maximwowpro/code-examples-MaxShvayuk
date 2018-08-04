#include <string>

#include <SFML/Graphics.hpp>

#include "map.h"
#include "constants.h"

using namespace sf;

//const int mapW = 19;//map width (in tiles), to conwert in pixels, * it in side of your tile
//const int mapH = 10;//map height

std::string tileMap[mapH] = {
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "    0                           ",
    "00000                           ",
    "                 0              ",
    "                 0       0      ",
    "          0      0       0000000",
    "          00000000000           ",
    "                         0      ",
    "                                ",
    "     0            0             ",
    "000000      000   00000000000000",
    "000000                          ",
    "0000000                         ",
    "0000000000000                   ",
    "00000000000000    0            0",
    "00000000000000000000000000000000"
};

void setMap(RenderWindow& window, std::string adress){
    //&window - link to window, adress - adress to your image with tiles
    Image mapImage;
    mapImage.loadFromFile(adress);
    Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    Sprite mapSprite;
    mapSprite.setTexture(mapTexture);

    for(int i=0; i<mapH; i++)
        for(int j=0; j<mapW; j++){
            if(tileMap[i][j] == '0'){ mapSprite.setTextureRect(IntRect(0 ,224, 32, 32)); }
            if(tileMap[i][j] == ' '){ mapSprite.setTextureRect(IntRect(224, 0, 32, 32)); }
            mapSprite.setPosition(j*32, i*32);
            window.draw(mapSprite);
        }
    return;
}
