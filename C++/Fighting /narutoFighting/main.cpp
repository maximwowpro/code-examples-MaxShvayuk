#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "constants.h"
#include "animation.h"
#include "background.h"
#include "enemies.h"
#include "map.h"
#include "player.h"
#include "camera.h"
#include "menu.h"

using namespace sf;

int main(void)
{
    RenderWindow window(VideoMode(windowW, windowH), "Naruto fighting");
    menu(window);

    View camera;
    camera.reset(FloatRect(0,400, cameraW, cameraH) );

    Clock clock;

    Player p1("images/naruto.png", 200, 200, 930, 0, 55, 75, "player1", "Naruto");
    p1.setPortrait(280, 0, 130, 150);
    p1.setHealthBar(5536, 321, 300, 22);
    Player p2("images/jiraiya.png", 300, 500, 1165, 0, 78, 80, "player2", "Jiraya");
    p2.setPortrait(280, 5, 125, 150);
    p2.setHealthBar(5067, 360, 300, 22);

    Font font;//шрифт
    font.loadFromFile("fonts/ninjanaruto.ttf");//передаем нашему шрифту файл шрифта
    Text text1(p1.character, font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text1.setColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    text1.setPosition(150 , 15 );//задаем позицию текста, центр камеры
    Text text2(p2.character, font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    text2.setColor(Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    text2.setPosition(cameraW - 150 - 100 , 15 );//задаем позицию текста, центр камеры

    std::list <Base*> enemies;
    std::list <Base*>::iterator it;
    enemies.push_back(new Enemy("images/kakashi.png", 800, 500,  125, 170, 40, 60, "hardEnemy", "Hatake Cacashi"));
    enemies.push_back(new Enemy("images/pain.png",    600, 400, 1075,  0, 40, 85, "hardEnemy", "Pain"));
    enemies.push_back(new Enemy("images/orochimaru.png",   900,  270, 1055, 0, 46, 70, "hardEnemy", "Orochimaru"));
    enemies.push_back(new Enemy("images/jugo.png",    300,  50, 1050, 0, 72, 65, "hardEnemy", "Jugo"));
    enemies.push_back(new Enemy("images/sasuke.png",  500, 300, 1185, 0, 55, 70, "hardEnemy", "Sasuke"));

    Music music;//создаем объект музыки
    music.openFromFile("sounds/narutomaintheme.ogg");//загружаем файл
    music.play();//воспроизводим музыку

    SoundBuffer buffer1;
    buffer1.loadFromFile("sounds/naruto/dattebayo.wav");// тут загружаем в буфер что то
    sf::Sound sound1;
    sound1.setBuffer(buffer1);

    SoundBuffer buffer2;
    buffer2.loadFromFile("sounds/jiraya/02B9_0000.wav");// тут загружаем в буфер что то
    sf::Sound sound2;
    sound2.setBuffer(buffer2);

    Texture timerTexture; timerTexture.loadFromFile("images/effects.png");
    Sprite timerSprite(timerTexture); timerSprite.setTextureRect(IntRect(760, 150, 25, 35) ); timerSprite.setPosition(480, 300);
    float startFightTimer = 0;

    Texture t1; t1.loadFromFile("images/naruto.png");

    while(window.isOpen() ){
        float time = clock.getElapsedTime().asMicroseconds();
        startFightTimer += time;
        clock.restart();
        time /= 800;

        Event event;
        while(window.pollEvent(event) ){
            if(event.type == Event::Closed) window.close();
        }

        p1.update(time);
        p2.update(time);
        for (it = enemies.begin(); it != enemies.end();) {
            (*it)->update(time);
            if ((*it)->isAlive == false) { it = enemies.erase(it); }//delete it; }
            else it++;
        }

        for (it = enemies.begin(); it != enemies.end(); it++){//kill the enemies
            if ((*it)->getRect().intersects(p1.getRect()))
                if ((*it)->name == "hardEnemy")
                {
                    if ((p1.dy>0) && (p1.onGround == false)) { (*it)->dx = 0; p1.dy = -0.2; (*it)->health = 0; sound1.play(); }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
                    else {
                        p1.health>0 ? p1.health -= 5 : p1.health = 0;
                    }
                }
            if ((*it)->getRect().intersects(p2.getRect()))
                if ((*it)->name == "hardEnemy")
                {
                    if ((p2.dy>0) && (p2.onGround == false)) { (*it)->dx = 0; p2.dy = -0.2; (*it)->health = 0; sound2.play();}//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
                    else {
                        p2.health>0 ? p2.health -= 5 : p2.health = 0;
                    }
                }
        }

        window.clear(Color::White);

        setBackgound(window, "images/konohaBackground.png", 0, 0, windowW, windowH);//draw background
        setMap(window, "images/woodTiles.png");

        setPlayerCoordinateForView(camera, p1.x, p1.y);

        if(startFightTimer < 3100000){
            timerSprite.setTextureRect(IntRect(95 + 28*(2 - (int)(startFightTimer-1000000)/1000000), 760, 28, 35) );
            timerSprite.setScale(4, 4);
            window.draw(timerSprite);
        }

//        Texture q; q.loadFromFile("images/test.jpg");
//        Sprite qs; qs.setTexture(q);
//        qs.setTextureRect(IntRect(0+200, 200, -200, 100));
//        qs.setPosition(300, 300);
//        window.draw(qs);

        window.draw(text1);//рисую этот текст
        window.draw(text2);//рисую этот текст

        window.setView(camera);
        window.draw(p1.sprite); window.draw(p1.portrait); window.draw(p1.healthBar);
        window.draw(p2.sprite); window.draw(p2.portrait); window.draw(p2.healthBar);



        for(it = enemies.begin(); it!=enemies.end(); it++){
            window.draw( (*it)->sprite );
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10) );
    }


















    return 0;
}




















































//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <chrono>
//#include <thread>
//#include <sstream>
//#include <list>
//#include <string>

//#include "animation.h"
//#include "background.h"
//#include "enemies.h"
//#include "map.h"
//#include "player.h"

//using namespace sf;

//const int W = 610;//width
//const int H = 320;//height

//int main(void)
//{
//    RenderWindow window(VideoMode(610, 320), "Naruto fighting");

//    Clock clock;

//    Player p1("images/naruto_sheet.png", 200, 200, 20, 245, 40, 50, "Naruto");

//    while(window.isOpen() ){
//        float time = clock.getElapsedTime().asMicroseconds();
//        clock.restart();
//        time /= 800;

//        Event event;
//        while(window.pollEvent(event) ){
//            if(event.type == Event::Closed) window.close();

//        }

//        p1.update(time);

//        window.clear(Color::White);

//        setBackgound(window, "images/konohaBackgroundSmall.png", 0, 0, W, H);//draw background
//        setMap(window, "images/woodTiles.png");

//        window.draw(p1.sprite);
//        window.display();
//        std::this_thread::sleep_for(std::chrono::milliseconds(10) );
//    }


















//    return 0;
//}

