#include "Block.h"

#include "../../game.h"

Block::Block(int x_axis, int y_axis, bool tickEnabled): BaseActor(x_axis, y_axis, tickEnabled)
{
    this->tickEnabled_=false;
    this->actor_sprite_= MyFramework::createSpriteInFramework("data/01-Breakout-Tiles.png");
}

bool Block::init(int blockType)
{
    //this->actor_sprite_= MyFramework::createSpriteInFramework("data/01-Breakout-Tiles.png");
    this->tickEnabled_ = true;
    return true;
}

void Block::reset()
{
    BaseActor::reset();
}

void Block::tick()
{
    BaseActor::tick();

}

void Block::setPosition(int x, int y)
{
    x_axis_ = x;
    y_axis_ = y;
}
