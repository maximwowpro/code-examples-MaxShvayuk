#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>

#define mapW 32//map width (in tiles), to conwert in pixels, * it in side of your tile
#define mapH 22//map height
#define tileSize 32//size of side of one tile in pixels

extern std::string tileMap[mapH];//array in which we "draw" the location

#define windowW 1024//window width
#define windowH 704//window height

//#define cameraW 640
//#define cameraH 480

#define cameraW 1024
#define cameraH 704


#endif // CONSTANTS_H

