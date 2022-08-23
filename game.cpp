#define _WINDOWS true

#include "Class/Core/Framework.h"
#include "Class/Core/Input.h"

#include "game.h"


#include "Class/Ball/Ball.h"
#include "Class/Core/GameInstance.h"
#include "Class/Player/Player.h"

Input* input_ = Input::instance();



void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
    width = 800;
    height = 600;
    fullscreen = false;
}

bool MyFramework::Init()
{
   
   
    GameInstance::getInstance()->beginPlay();
    
    return true;
}

void MyFramework::Close()
{
}

bool MyFramework::Tick()
{
    GameInstance::getInstance()->tick();
    
    return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
    if(!isReleased)
        GameInstance::getInstance()->SpawnBall();
    
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

void MyFramework::getSpriteSizeInFramework(Sprite* sprite,  int& width, int &height)
{
    getSpriteSize(sprite, width, height);
}

void MyFramework::setSpriteSizeInFramework(Sprite* sprite,  int width, int height)
{
    setSpriteSize(sprite, width, height);
}

void MyFramework::destroySpriteInFramework(Sprite* sprite)
{
    destroySprite(sprite);
}

void MyFramework::getScreenSizeFromFramework( int& w, int &h)
{
    getScreenSize(w,h);
}

void MyFramework::drawSpriteInFramework(Sprite* sprite, int x_axis, int y_axis)
{
    drawSprite(sprite,x_axis,y_axis);
}

Sprite* MyFramework::createSpriteInFramework(const char* path)
{
    return createSprite(path);
}

int main(int argc, char* argv[])
{
    return run(new MyFramework);
}
