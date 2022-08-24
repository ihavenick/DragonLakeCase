#include "Buff.h"

#include <cstdlib>

#include "../../game.h"
#include "../Ball/Ball.h"
#include "../Core/GameInstance.h"

Buff::Buff(int x_axis, int y_axis, bool tickEnabled): BaseActor(x_axis, y_axis, tickEnabled)
{
    this->actor_sprite_= MyFramework::createSpriteInFramework("data/59-Breakout-Tiles.png");
}

void Buff::tick()
{
    BaseActor::tick();
    y_axis_++;

    int w, h;
    MyFramework::getScreenSizeFromFramework(w, h);


    auto game = GameInstance::getInstance();

    if(doCollideWith(game->getPlayer()))
    {
        if(isPositive)
            game->SpawnBall(true);
        else
        {
            int w, h;
            MyFramework::getScreenSizeFromFramework(w,h);
            
            game->getBall()->setPosition(w,h / 2);
        }

            
        game->removeFromScreen(this);
    }
    
    if (y_axis_ > h)
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
