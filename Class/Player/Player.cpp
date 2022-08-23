#include "Player.h"

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
        moveInput(-10);
    else if (rightPressed && !leftPressed)
        moveInput(+10);
}

void Player::moveInput(int xAxis)
{
    x_axis_ += xAxis;
}

void Player::init(Sprite* test)
{
    actor_sprite_ = test;
}



