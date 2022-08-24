#include "BaseActor.h"

#include <cstdlib>

#include "GameInstance.h"
#include "../../game.h"
#include "../Block/Block.h"
#include "../Buff//Buff.h"
#include "../Ball//Ball.h"

void BaseActor::drawActor() const
{
    if(actor_sprite_!=nullptr)
    MyFramework::drawSpriteInFramework(actor_sprite_, x_axis_, y_axis_);
}



int BaseActor::getTag()
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
    int width_ = 0;
    int height_ = 0;
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
    int sW, sH;
    
    
    if(atag==0)
    {
        //random for create powered enemies or weaker
        const int isPowerFull = rand() % 2; //i hate this randomers. gives same numbers generally
        const auto e = new Block(50,50,true);
        e->init(isPowerFull);
        MyFramework::getSpriteSizeInFramework(e->getSprite(),sW,sH);
        MyFramework::setSpriteSizeInFramework(e->getSprite(),sW/10,sH/10);
        return e;
    }
    if(atag==1)
    {
        
        const int isPositive = rand() % 2; 
        const auto e = new Buff(1,1,true);
        e->init(isPositive);
        MyFramework::getSpriteSizeInFramework(e->getSprite(),sW,sH);
        MyFramework::setSpriteSizeInFramework(e->getSprite(),sW/5,sH/5);
        return e;
    }

    if(atag==2)
    {
        auto ball = GameInstance::getInstance()->getBall();
        
        const auto e = new Ball(ball->getXAxis(), ball->getYAxis(),true);

        e->x_speed_ = ball->x_speed_ * -1;

        
        return e;
    }

    if(atag==4)
    {
        int w,h;
        MyFramework::getScreenSizeFromFramework(w,h);
        const auto gameOver = MyFramework::createSpriteInFramework("data/gameover.png");
        MyFramework::drawSpriteInFramework(gameOver, w/2, h/2);
    }
  

   
}

Sprite* BaseActor::getSprite()
{
    return actor_sprite_;
}

bool BaseActor::init()
{
   // visibleSize = Director::getInstance()->getVisibleSize();
    // origin = Director::getInstance()->getVisibleOrigin();

    //TODO test if this better here
    // auto rectBody = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    // rectBody->setContactTestBitmask(true);
    // this->setPhysicsBody(rectBody);

    return true;
}

void BaseActor::reset()
{
}