#include "base.hpp"

Base::Base() {
    xCoordinate_ = 0;
    yCoordinate_ = 0;
    isMoving_ = false;
    isAlive_ = true;
    direction_ = LEFT;
}

int Base::getXCoordinate() {
    return xCoordinate_;
}

int Base::getYCoordinate() {
    return yCoordinate_;
}

void Base::setCoordinates(int X, int Y)
{
    xCoordinate_ = X;
    yCoordinate_ = Y;
}

void Base::countNextFrameCoordinate() {
    if(isMoving_ == true && isAlive_ == true)
    {
        switch (direction_) {
        case(LEFT):
            xCoordinate_ -= 1;
            break;
        case(RIGHT):
            xCoordinate_ += 1;
            break;
        case(UP):
            yCoordinate_ -= 1;
            break;
        case(DOWN):
            yCoordinate_ += 1;
            break;
        }
    }
}

void Base::setDirection(direction newDirection)//changes direction
{
    direction_ = newDirection;
}

Base::direction Base::getDirection()//хз нужно ли оно
{
    return direction_;
}

void Base::setMovingState(bool newMovingState)//changes isMoving_
{
    isMoving_ = newMovingState;
}

void Base::setAliveState(bool newAliveState)//changes isAlive_
{
    isAlive_ = newAliveState;
}


















