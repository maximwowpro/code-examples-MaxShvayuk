#include <SFML/Graphics.hpp>

#include "constants.h"
#include "camera.h"

using namespace sf;

void setPlayerCoordinateForView(View& camera, float x, float y){

    if (y < cameraH /2) y = cameraH /2 ;
    if (y > windowH - cameraH /2) y = windowH - cameraH /2;

    if (x < cameraW /2 ) x = cameraW/2;
    if (x > windowW - cameraW /2 ) x = windowW - cameraW/2;

    camera.setCenter(x, y);
    return;
}

