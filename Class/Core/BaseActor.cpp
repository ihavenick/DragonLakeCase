#include "BaseActor.h"

#include <cstdlib>

#include "GameInstance.h"
#include "../../game.h"
#include "../Block/Block.h"
#include "../Buff//Buff.h"
#include "../Ball//Ball.h"

void BaseActor::drawActor() const                             //draw logic for framework
{
    if(actor_sprite_!=nullptr)
    MyFramework::drawSpriteInFramework(actor_sprite_, x_axis_, y_axis_);
}



int BaseActor::getTag()    //get tag for logics
{
    return tag_;
}

BaseActor::BaseActor( int x_axis, int y_axis, bool tickEnabled)   
{
    this->x_axis_ = x_axis;
    this->y_axis_ = y_axis;
    this->tickEnabled_ = tickEnabled;
}

void BaseActor::tick()
{
    drawActor();
    
    if (!tickEnabled_)
        return;
    
}

BaseActor::~BaseActor()
{
   MyFramework::destroySpriteInFramework(actor_sprite_);
}

bool BaseActor::doCollideWith(const BaseActor* base_actor) const
{
    int width_ = 0;  // width of the actor
    int height_ = 0; // height of the actor
    if (!actor_sprite_)
        return false;

    MyFramework::getSpriteSizeInFramework(actor_sprite_, width_, height_);

    int otherActorWidth = 0;
    int otherActorHeight = 0;
    if (!base_actor->actor_sprite_)
        return false;

    MyFramework::getSpriteSizeInFramework(base_actor->actor_sprite_, otherActorWidth, otherActorHeight);

    //collision check with height and width
    return (x_axis_ + width_ > base_actor->x_axis_ && x_axis_ < base_actor->x_axis_ + otherActorWidth && y_axis_ +
               height_ > base_actor->y_axis_ && y_axis_ < base_actor->y_axis_ + otherActorHeight)
               ? true
               : false;
}


int BaseActor::getXAxis() const
{
    return x_axis_;
}

int BaseActor::getYAxis() const
{
    return y_axis_;
}

void BaseActor::Collided()
{
}

BaseActor* BaseActor::create(int atag)
{
    int sW, sH;  //sprite width and height
    
    if(atag==0)   //block
    {
        //random for create powered blocks or weaker
        const int isPowerFull = rand() % 2; //i hate this randomers. gives same numbers generally
        const auto blck = new Block(50,50,true);
        blck->init(isPowerFull);
        MyFramework::getSpriteSizeInFramework(blck->getSprite(),sW,sH);
        MyFramework::setSpriteSizeInFramework(blck->getSprite(),sW/7,sH/10);
        return blck;
    }
    if(atag==1)    //buff
    {
        const int isPositive = rand() % 2; 
        const auto e = new Buff(1,1,true);
        e->init(isPositive);
        MyFramework::getSpriteSizeInFramework(e->getSprite(),sW,sH);
        MyFramework::setSpriteSizeInFramework(e->getSprite(),sW/5,sH/5);
        return e;
    }

    if(atag==2) //ball
    {
        auto ball = GameInstance::getInstance()->getBall();
        const auto bll = new Ball(ball->getXAxis(), ball->getYAxis(),true);
        bll->x_speed_ = ball->x_speed_ * -1;
        
        return bll;
    }

    if(atag==4 || atag == 5) //game over and win screens
    {
        int w,h; // screen width and heifht
        MyFramework::getScreenSizeFromFramework(w,h);
        const auto gameOverSprite = atag == 4 ? MyFramework::createSpriteInFramework("data/gameover.png") : MyFramework::createSpriteInFramework("data/youwin.png");
        MyFramework::setSpriteSizeInFramework(gameOverSprite, w/2, h/2);
        MyFramework::getSpriteSizeInFramework(gameOverSprite,sH,sW);
        const auto gameOverActor = new BaseActor(w/2 - (sW /2),h/2 -(sH /2),false);
        gameOverActor->actor_sprite_= gameOverSprite;
        return gameOverActor;
    }
   
}

Sprite* BaseActor::getSprite()
{
    return actor_sprite_;
}

bool BaseActor::init()
{
    return true;
}

void BaseActor::reset()
{
}