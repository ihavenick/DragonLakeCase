#pragma once

class Input
{

    static Input* _instance;
    
    bool b_is_left_key_pressed_ = false;
    bool b_is_right_key_pressed_ = false;
    
public:

    static Input* instance();
    void setKeyPressed(bool IsLeft, bool Pressed);
    bool getKeyPressed(bool IsLeft) const;
    
};
