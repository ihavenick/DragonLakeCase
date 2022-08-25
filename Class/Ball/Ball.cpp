#include "Ball.h"

#include "../../game.h"
#include "../Core/GameInstance.h"

Ball::Ball(int x_axis, int y_axis, bool tickEnabled): BaseActor(x_axis, y_axis, tickEnabled)
{
    this->actor_sprite_= MyFramework::createSpriteInFramework("data/64-Breakout-Tiles.png");  //default sprite
    this->tag_ = 3;                                                                                //trying to tag the ball
}

void Ball::tick()
{
    BaseActor::tick();

    int w, h;  //width and height of the screen
    MyFramework::getScreenSizeFromFramework(w, h);
    
    x_axis_+=x_speed_;
    y_axis_+=y_speed_;

    // if ball collision top of the sprite invert x speed
    
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
        GameInstance::getInstance()->ballOutofScreen(this);
        
    }
}

void Ball::changeDirection(BaseActor* actor)

{
    int otherActorWidth ,otherActorHeight;
    int ballWidth, ballHeight;
    
    
    MyFramework::getSpriteSizeInFramework(actor->getSprite(), otherActorWidth, otherActorHeight);
    MyFramework::getSpriteSizeInFramework(actor_sprite_, ballWidth, ballHeight);
    
   
    //if actor collide top of the sprite invert x speed
    if(actor->getYAxis()<=y_axis_+ballHeight && actor->getYAxis()>=y_axis_)
    {
        y_speed_*=-1;
    }
    //if actor collide bottom of the sprite invert x speed
    if(actor->getYAxis()+otherActorHeight<=y_axis_+ballHeight && actor->getYAxis()+otherActorHeight>=y_axis_)
    {
        y_speed_*=-1;
    }

   // if ball collide with right side of the actor invert x speed
       if(x_axis_+ballWidth>=actor->getXAxis() && x_axis_+ballWidth<=actor->getXAxis()+otherActorWidth)
   {
       x_speed_*=-1;
   }
   //if ball collide with left side of the actor invert x speed
   if(x_axis_<=actor->getXAxis()+otherActorWidth && x_axis_>=actor->getXAxis())
   {
       x_speed_*=-1;
   }

    
    
    // if(x_axis_<actor->getXAxis())
    // {
    //     x_speed_*=-1;
    // }
    // if(x_axis_>actor->getXAxis()+otherActorWidth)
    // {
    //     x_speed_*=-1;
    // }
    //
    //
    //
    // if(y_axis_ < actor->getYAxis())
    // {
    //     y_speed_*=-1;
    // }
    //
    //
    // if(y_axis_ > actor->getYAxis()+otherActorHeight)
    // {
    //     y_speed_ *= -1;
    //
    //     if (x_axis_ < actor->getXAxis() + otherActorWidth)
    //     {
    //         x_speed_ *= -1;
    //     }
    // }
    //
    //
    //  if(y_axis_ < actor->getYAxis()+otherActorHeight && y_axis_ > actor->getYAxis())
    //  {
    //      y_speed_*=-1;
    //  }
    //  
     
   

   
   
    
    


    
    // if(y_axis_<actor->getYAxis()+otherActorHeight || y_axis_>actor->getYAxis())
    // {
    //     y_speed_*=-1;
    // }

    // if(actor->getXAxis()<x_axis_ || actor->getXAxis()>x_axis_)
    //     y_speed_*=-1;
    //
    // if(actor->getYAxis()<y_axis_ || actor->getYAxis()>y_axis_)
    //     x_speed_*=-1;
   

    
    //  x_speed_=-x_speed_;
   // y_speed_=-y_speed_;
}

void Ball::reset(int x, int y)
{
    x_axis_=x;
    y_axis_=y;
    x_speed_=1;
    y_speed_=-1;
}

void Ball::setPosition(int get_x_axis, int get_x_axis1)
{
    x_axis_=get_x_axis;
    y_axis_=get_x_axis1;
}
