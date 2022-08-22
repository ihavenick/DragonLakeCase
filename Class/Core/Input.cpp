#include "Input.h"


Input* Input::_instance = nullptr;

Input* Input::instance()
{
    if (_instance == nullptr) {
        _instance = new Input();
    }
    return _instance;
}


void Input::setKeyPressed(bool IsLeft, bool Pressed)
{
    (IsLeft ? b_is_left_key_pressed_ : b_is_right_key_pressed_) = Pressed;
}

bool Input::getKeyPressed(bool IsLeft) const
{
    return (IsLeft ? b_is_left_key_pressed_ : b_is_right_key_pressed_);
}
