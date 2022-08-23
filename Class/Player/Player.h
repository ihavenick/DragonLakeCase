#pragma once
#include "../Core/BaseActor.h"

class Sprite;

class Player : public BaseActor
{

private:
    int player_speed_;
    

public:

    Player( int x_axis, int y_axis, bool tickEnabled);

    virtual void tick() override;
    void checkInBounds();

    void moveInput(int xAxis);
    void init(Sprite* test);
};
