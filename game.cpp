#define _WINDOWS true

#include "Class/Core/Framework.h"
#include "Class/Core/Input.h"

#include "game.h"


#include "Class/Player/Player.h"

Input* input_ = Input::instance();
Player* Pl;

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
    width = 1600;
    height = 700;
    fullscreen = false;
}

bool MyFramework::Init()
{
    int w, h;
    int sW, sH;
    getScreenSize(w, h );
    Sprite* test = createSprite("data/49-Breakout-Tiles.png");
   
    getSpriteSize(test,sW,sH);
    setSpriteSize(test,sW/10,sH/10);
    getSpriteSize(test,sW,sH);
    Pl = new Player(test,w/2 - (sW /2),h - sH,true);
   
    
    return true;
}

void MyFramework::Close()
{
}

bool MyFramework::Tick()
{
    //drawTestBackground();
   Pl->tick();
    return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
    Pl->drawActor();
}

void MyFramework::onKeyPressed(FRKey k)
{
    if (k == FRKey::LEFT)
        input_->setKeyPressed(true, true);

    if (k == FRKey::RIGHT)
        input_->setKeyPressed(false, true);
}

void MyFramework::onKeyReleased(FRKey k)
{
    if (k == FRKey::LEFT)
        input_->setKeyPressed(true, false);

    if (k == FRKey::RIGHT)
        input_->setKeyPressed(false, false);
}

const char* MyFramework::GetTitle()
{
    return "Arcanoid";
}

void MyFramework::getSpriteSizeInFramework(Sprite* sprite, int width, int height)
{
    getSpriteSize(sprite, width, height);
}

void MyFramework::destroySpriteInFramework(Sprite* sprite)
{
    destroySprite(sprite);
}

void MyFramework::drawSpriteInFramework(Sprite* sprite, int x_axis, int y_axis)
{
    drawSprite(sprite,x_axis,y_axis);
}

int main(int argc, char* argv[])
{
    return run(new MyFramework);
}
