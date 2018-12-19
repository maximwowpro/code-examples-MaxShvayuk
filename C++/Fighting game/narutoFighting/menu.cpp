#include "menu.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow & window) {
    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/play.png");
    menuTexture3.loadFromFile("images/exit.png");
    menuBackground.loadFromFile("images/menu.png");

    Sprite menu1(menuTexture1), menu3(menuTexture3), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu3.setPosition(100, 150);
    menuBg.setPosition(0, 0);
    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu3.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));
        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
            if (menuNum == 3)  { window.close(); isMenu = false; }
        }
        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu3);
        window.display();
    }
    ////////////////////////////////////////////////////
}
