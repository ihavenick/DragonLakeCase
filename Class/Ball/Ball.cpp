#include "Ball.h"

#include "../../game.h"
#include "../Core/GameInstance.h"

Ball::Ball(int x_axis, int y_axis, bool tickEnabled): BaseActor(x_axis, y_axis, tickEnabled)
{
    this->actor_sprite_= MyFramework::createSpriteInFramework("data/64-Breakout-Tiles.png");
    this->tag_ = 3;
}

void Ball::tick()
{
    BaseActor::tick();

    int w, h;
    MyFramework::getScreenSizeFromFramework(w, h);
    
    x_axis_+=x_speed_;
    y_axis_+=y_speed_;

    if(x_axis_<0)
    {
        x_axis_=0;
        x_speed_*=-1;
    }
    if(x_axis_>=w)
    {
        x_axis_=w-1;
        x_speed_*=-1;
    }
    if(y_axis_<0)
    {
        y_axis_=0;
        y_speed_*=-1;
    }
    if(y_axis_>=h)
    {
        //ball is out of screen
        GameInstance::getInstance()->ballOutofScreen();
        
    }
}

void Ball::changeDirection()
{
    x_speed_=-x_speed_;
    y_speed_=-y_speed_;
}

void Ball::reset(int x, int y)
{
    x_axis_=x;
    y_axis_=y;
    x_speed_=1;
    y_speed_=1;
}
