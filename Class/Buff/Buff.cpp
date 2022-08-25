#include "Buff.h"

#include <cstdlib>

#include "../../game.h"
#include "../Ball/Ball.h"
#include "../Core/GameInstance.h"

Buff::Buff(int x_axis, int y_axis, bool tickEnabled): BaseActor(x_axis, y_axis, tickEnabled)
{
    this->actor_sprite_= MyFramework::createSpriteInFramework("data/59-Breakout-Tiles.png");
    this->tag_ = 2;
}

void Buff::tick()
{
    BaseActor::tick();
    y_axis_++;

    int w, h;
    MyFramework::getScreenSizeFromFramework(w, h);


    const auto game = GameInstance::getInstance();

    if(doCollideWith(game->getPlayer()))
    {
        if(isPositive)                      //positive buff
            game->SpawnBall(1, true);     // split balls
        else
        {
            int w, h; // width and height of the screen
            MyFramework::getScreenSizeFromFramework(w,h);        //if negative buff, then teleport to ball half of screen
            
            game->getBall()->setPosition(w,h / 2);
        }

            
        game->removeFromScreen(this);
    }
    
    if (y_axis_ > h)   // if out of screen , remove buff
    {
       game->removeFromScreen(this);
    }

    
}

void Buff::init(int is_positive)
{

    int w, h;
    MyFramework::getScreenSizeFromFramework(w,h);

    y_axis_ = rand() % ( h);
    x_axis_ = rand() % ( w);
    
    
    isPositive = is_positive;
}
