#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP

#include <vector>
#include <string>
#include <list>
//#include <chrono>

#include <player.hpp>
#include <enemy.hpp>
#include <bullet.hpp>

class Battlefield
{
private:
    std::vector <std::string> area_;
    int AREA_X_LINES = 80;
    int AREA_Y_LINES = 20;
    std::vector <Enemy> enemies_;
    std::vector <Bullet> bullets_;
    Player player_;
    enum direction {LEFT = 0, RIGHT, UP, DOWN, SPACE} button_;//in what direction object moves
private:
    void generateRandomWalls();//use ONLY in constructor one time
    void fillAreaFirstTime();//use ONLY in constructor one time
    bool checkCoordinatesForPlayerAndEnemy(int x, int y);//if coordinates are free return true
    void addPlayerAndEnemyToArea(int x, int y, std::vector <std::string> );
public:
    Battlefield();
    void spawnEnemiesRandomLocations(int numberEnemies);//use ONLY in constructor one time
    void drawBattlefield();
    void buttonPress();
    void updatePlayer();
    void updateEnemies();
    void updateBullets();
    void updateTimer();
    void updateLives();
    void updateScores();
    bool isGameOvered();
    bool isVictory();
    ~Battlefield(){}
};

#endif // BATTLEFIELD_HPP

