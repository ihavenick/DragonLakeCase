#define _WINDOWS true

#include "Class/Core/Framework.h"
#include "Class/Core/Input.h"
#include "game.h"
#include "Class/Ball/Ball.h"
#include "Class/Core/GameInstance.h"


Input* input_ = Input::instance();



void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
    width = screenWidth;
    height = screenHeight;
    fullscreen = isFullscreen;
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
    mouseX = x;
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
    const auto game = GameInstance::getInstance();
    
    if(!isReleased && !game->getBall())
    {
        game->SpawnBall(mouseX, false);
        
    }
    
    if(!isReleased && game->getGameOver())
    {
        game->reset();
    }
    
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

void MyFramework::setWindowParameters(int witdh, int height, bool fullscreen)
{
    screenHeight = height;
    screenWidth = witdh;
    isFullscreen = fullscreen;
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
    const auto Framework = new MyFramework;
    
    //get window size from arguments -width, -height, -fullscreen
    if(argc > 1)
    {
        int width = 800;
        int height = 600;
        bool fullscreen = false;
        for(int i = 1; i < argc; i++)
        {
            if(strcmp(argv[i], "-width") == 0)
            {
                width = atoi(argv[i+1]);
                printf("%d",width);
                i++;
            }
            else if(strcmp(argv[i], "-height") == 0)
            {
                height = atoi(argv[i+1]);
                i++;
            }
            else if(strcmp(argv[i], "-fullscreen") == 0)
            {
                fullscreen = true;
            }
        }

        Framework->setWindowParameters(width, height, fullscreen);
    }
    
    return run(Framework);
}
