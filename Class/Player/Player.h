#pragma once
#include "../Core/BaseActor.h"

class Sprite;

class Player : public BaseActor
{

private:
    int player_speed_;
    

public:

    Player(Sprite* player_sprite, int x_axis, int y_axis, bool tickEnabled);

    virtual void tick() override;
    
    void moveInput(int xAxis);
};
