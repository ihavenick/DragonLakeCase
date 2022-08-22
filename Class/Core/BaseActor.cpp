#include "BaseActor.h"
#include "../../game.h"


void BaseActor::drawActor() const
{
    
    MyFramework::drawSpriteInFramework(actor_sprite_, x_axis_, y_axis_);
}

BaseActor::BaseActor(Sprite* actor_sprite, int x_axis, int y_axis, bool tickEnabled)
{
    this->actor_sprite_ = actor_sprite;
    this->x_axis_ = x_axis;
    this->y_axis_ = y_axis;
    this->tickEnabled_ = tickEnabled;
}

void BaseActor::tick()
{
    if (!tickEnabled_)
        return;

    drawActor();
}

BaseActor::~BaseActor()
{
   MyFramework::destroySpriteInFramework(actor_sprite_);
}

bool BaseActor::doCollideWith(const BaseActor* base_actor) const
{
    int width_ = 0;
    int height_ =0;
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