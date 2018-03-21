#ifndef BASE_HPP
#define BASE_HPP
//Base is a class with common variables for Player, Enemy, Bullet classes

class Base
{
private:
    int xCoordinate_;
    int yCoordinate_;
    bool isMoving_;//if moves = true, if stays = false
    bool isAlive_;
public:
    enum direction {LEFT = 0, RIGHT, UP, DOWN} direction_;//in what direction object moves
    Base();
    int getXCoordinate();
    int getYCoordinate();
    void setCoordinates(int X, int Y);
    void countNextFrameCoordinate();
    void setDirection(direction newDirection);//changes direction
    direction getDirection();//хз нужно ли оно
    void setMovingState(bool newMovingState);//changes isMoving_
    void setAliveState(bool newAliveState);//changes isAlive_
    ~Base(){}
};






#endif // BASE_HPP


