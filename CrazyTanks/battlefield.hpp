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
    const int AREA_X_LINES = 80;
    const int AREA_Y_LINES = 20;
    //std::chrono::system_clock::time_point clock_;
    std::vector <Enemy> enemies_;
    std::vector <Bullet> bullets_;
    Player player_;
    char buttonPress_;//what button was pressed
private:
    void generateRandomWalls();//use ONLY in constructor one time
    void fillAreaFirstTime();//use ONLY in constructor one time
    void spawnEnemiesRandomLocations(int numberEnemies);//use ONLY in constructor one time
    bool checkCoordinatesForPlayerAndEnemy(int x, int y);//if coordinates are free return true
    void addPlayerAndEnemyToArea(int x, int y, std::vector <std::string> );
public:
    Battlefield(int numberEnemies);
    void drawBattlefield();
    void buttonPress();
    void updatePlayer();
    void updateEnemies();
    void updateBullets();
    void updateTimer();
    void updateLives();
    void updateScores();
    ~Battlefield(){}
};

#endif // BATTLEFIELD_HPP

