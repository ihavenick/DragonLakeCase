#include "BaseActor.h"

#include <cstdlib>

#include "../../game.h"
#include "../Block/Block.h"


void BaseActor::drawActor() const
{
    if(actor_sprite_)
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
    int height_ =0;
    if(actor_sprite_)
    MyFramework::getSpriteSizeInFramework(actor_sprite_, width_, height_);
    return base_actor->getXAxis() >= x_axis_ && base_actor->getXAxis() <= x_axis_ + width_ && base_actor->getYAxis() >= y_axis_ && base_actor->getYAxis() <= y_axis_ + height_ ? true : false;
}


int BaseActor::getXAxis() const
{
    return x_axis_;
}

int BaseActor::getYAxis() const
{
    return y_axis_;
}

BaseActor* BaseActor::create(int atag)
{
    int sW, sH;
    
  
    
    if(atag==0)
    {
        //random for create powered enemies or weaker
        const int isPowerFull = rand() % 3; //i hate this randomers. gives same numbers generally
        const auto e = new Block(50,50,true);
        e->init(isPowerFull);
        MyFramework::getSpriteSizeInFramework(e->getSprite(),sW,sH);
        MyFramework::setSpriteSizeInFramework(e->getSprite(),sW/10,sH/10);
        return e;
    }

    if(atag==3)
    {
        
    }
   // const auto b = new Buff();
  //  b->init();
  //  return b;
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