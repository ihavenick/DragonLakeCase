#include "Ball.h"

#include "../../game.h"

Ball::Ball(int x_axis, int y_axis, bool tickEnabled): BaseActor(x_axis, y_axis, tickEnabled)
{
    this->actor_sprite_= MyFramework::createSpriteInFramework("data/63-Breakout-Tiles.png");
    this->tag_ = 3;
}

void Ball::tick()
{
    BaseActor::tick();
    x_axis_+=x_speed_;
    y_axis_+=y_speed_;
    
}
