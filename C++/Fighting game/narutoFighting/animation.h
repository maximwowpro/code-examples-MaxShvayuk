#ifndef ANIMATION_H
#define ANIMATION_H

#include<SFML/Graphics.hpp>

using namespace sf;

class Animation{
public:
    IntRect rect;//here we storage coordinates of current sprite
    Sprite sprite;

    Animation();
    //number - number № of sprite of animation (for example: 3 of 6 sprites)
    void setAnimationSprite(Texture& _texture, int _x0, int _y0, int _w, int _h, int _number, bool _isLeft);

    Sprite getAnimationSprite();
};



#endif  //ANIMATION_H

//#include <vector>
//#include<SFML/Graphics.hpp>

//using namespace sf;

//class Animation
//{
//public:
//    std::vector<IntRect> frames, frames_flip;//frames - масив кадров, frames_flip - повернутіе кадрі
//    float currentFrame, speed;//текущий кадр, скорость
//    bool flip, isPlaying;   // flip - зеркально или нет isPlaying - проигрывать или нет
//    Sprite sprite;

//    Animation(Texture t, int x, int y, int w, int h, int count, float Speed, int step)
//    {
//        speed = Speed;
//        sprite.setTexture(t);

//        currentFrame = 0;
//        isPlaying = true;
//        flip = false;

//        for(int i; i<count; i++)//тут создаем масив прямоугольников
//        {
//            frames.push_back(IntRect(x+i*step, y, w, h) );
//            frames_flip.push_back(IntRect(x+i*step+w, y, -w, h));

//        }
//    }

//    void tick(float time)
//    {
//        if (!isPlaying) return;

//        currentFrame += speed * time;

//        if (currentFrame > frames.size())
//        {
//            currentFrame -= frames.size();
//        }

//        int i = currentFrame;
//        sprite.setTextureRect( frames[i] );
//        if (flip) sprite.setTextureRect( frames_flip[i] );
//    }

//};



//class AnimationManager
//{

//public:
//    std::string currentAnim;
//    std::map <std::string, Animation> animList;

//    AnimationManager()
//    {}

//    ~AnimationManager()
//    { animList.clear();
//    }

//    void create(std::string name, Texture &t, int x, int y, int w, int h, int count, float speed, int step)
//    {
//        animList[name] = Animation(t, x, y, w, h, count, speed, step);
//        currentAnim = name;
//    }

//    //çàãðóçêà èç ôàéëà XML
//    //    void loadFromXML(std::string fileName,Texture &t)
//    //    {
//    //        TiXmlDocument animFile(fileName.c_str());

//    //        animFile.LoadFile();

//    //        TiXmlElement *head;
//    //        head = animFile.FirstChildElement("sprites");

//    //        TiXmlElement *animElement;
//    //        animElement = head->FirstChildElement("animation");
//    //        while(animElement)
//    //        {
//    //            Animation anim;
//    //            currentAnim = animElement->Attribute("title");
//    //            int delay = atoi(animElement->Attribute("delay"));
//    //            anim.speed = 1.0/delay; anim.sprite.setTexture(t);

//    //            TiXmlElement *cut;
//    //            cut = animElement->FirstChildElement("cut");
//    //            while (cut)
//    //            {
//    //                int x = atoi(cut->Attribute("x"));
//    //                int y = atoi(cut->Attribute("y"));
//    //                int w = atoi(cut->Attribute("w"));
//    //                int h = atoi(cut->Attribute("h"));

//    //                anim.frames.push_back( IntRect(x,y,w,h) );
//    //                anim.frames_flip.push_back( IntRect(x+w,y,-w,h)  );
//    //                cut = cut->NextSiblingElement("cut");
//    //            }

//    //            anim.sprite.setOrigin(0,anim.frames[0].height);

//    //            animList[currentAnim] = anim;
//    //            animElement = animElement->NextSiblingElement("animation");
//    //        }
//    //    }

//    void set(std::string name)
//    {
//        currentAnim = name;
//    }

//    void draw(RenderWindow &window,int x=0, int y=0)
//    {
//        animList[currentAnim].sprite.setPosition(x,y);
//        window.draw( animList[currentAnim].sprite );
//    }

//    void flip(bool b) {animList[currentAnim].flip = b;}

//    void tick(float time) {animList[currentAnim].tick(time);}

//    void pause() {animList[currentAnim].isPlaying=false;}

//    void play()  {animList[currentAnim].isPlaying=true;}

//    //    void play(std::string name)  {animList[name].isPlaying=true;}

//    //    bool isPlaying()  {return animList[currentAnim].isPlaying;}

//    //    float getH()  {return animList[currentAnim].frames[0].height;}

//    //    float getW() {return animList[currentAnim].frames[0].width;}

//};























