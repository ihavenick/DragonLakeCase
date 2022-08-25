#include "Block.h"

#include "../../game.h"
#include "../Core/GameInstance.h"

Block::Block(int x_axis, int y_axis, bool tickEnabled): BaseActor(x_axis, y_axis, tickEnabled)
{
    this->tickEnabled_=false;
    this->actor_sprite_= MyFramework::createSpriteInFramework("data/01-Breakout-Tiles.png");
}

bool Block::init(int blockType)
{
    
   if(blockType==1 && GameInstance::getInstance()->CanAbleToSpawnRedBlocks())
   {
       this->actor_sprite_= MyFramework::createSpriteInFramework("data/07-Breakout-Tiles.png");
       isPowerfull_=true;
   }
       
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

void Block::Collided()
{
    const auto game = GameInstance::getInstance();
    if (isPowerfull_ && game->getWeakBlockCount() > 0)
        return;


    durability_--;
    if (durability_ > 0)
    {
        if (durability_ == 1)
        {
            int sW, sH;
            this->actor_sprite_ = isPowerfull_
                                      ? MyFramework::createSpriteInFramework("data/06-Breakout-Tiles.png")
                                      : MyFramework::createSpriteInFramework("data/02-Breakout-Tiles.png");

            MyFramework::getSpriteSizeInFramework(actor_sprite_,sW,sH);
            MyFramework::setSpriteSizeInFramework(actor_sprite_,sW/7,sH/10);
        }
    }
    else
    {
         game->setBlockCount(-1, isPowerfull_);
        game->removeFromScreen(this);
        tickEnabled_ = false;
    }
}

bool Block::getIsPowered()
{   
    return isPowerfull_;
}

void Block::setPosition(int x, int y)
{
    x_axis_ = x;
    y_axis_ = y;
}
