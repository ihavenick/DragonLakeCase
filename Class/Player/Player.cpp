#include "Player.h"

#include "../../game.h"
#include "../Core/Input.h"

Player::Player( int x_axis, int y_axis, bool tickEnabled = true): BaseActor(x_axis,y_axis,tickEnabled)
{
}

void Player::tick()
{
    BaseActor::tick();
    

    const Input* inputInstance = Input::instance();
    const bool leftPressed= inputInstance->getKeyPressed(true);
    const bool rightPressed = inputInstance->getKeyPressed(false);

    if(leftPressed && !rightPressed)
        moveInput(-5);
    else if (rightPressed && !leftPressed)
        moveInput(+5);

    checkInBounds();
    
}

void Player::checkInBounds()
{

    int sW, sH;
    MyFramework::getSpriteSizeInFramework(actor_sprite_,sW,sH);
    
    int w, h;
    MyFramework::getScreenSizeFromFramework(w, h);
    if (x_axis_ < 0)
        x_axis_ = 0;
    else if (x_axis_ >= w - sW)
        x_axis_ = w - sW - 1;
}

void Player::moveInput(int xAxis)
{
    x_axis_ += xAxis;
}

void Player::init(Sprite* test)
{
    actor_sprite_ = test;
}



