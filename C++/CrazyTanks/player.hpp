#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

#include <base.hpp>

class Player:public Base
{
private:
    int scores_;
    int lives_;
    std::vector < std::vector <std::string> > images_;
    void setImages();//use ONLY in constructor
    void spawnOnBattlefield();////spawn Player at the middle of the bottom, use ONLY in constructor
    int LIVES_MAX = 3;//use ONLY in constructor
public:
    Player():Base()
    {
        scores_ = 0;
        lives_ = LIVES_MAX;
        setImages();
        spawnOnBattlefield();
    }
    std::vector <std::string> getImagePlayer();
    void setLives(int lives);
    int getLives();
    void setScores(int scores);
    int getScores();
    ~Player() {}
};

#endif // PLAYER_HPP





