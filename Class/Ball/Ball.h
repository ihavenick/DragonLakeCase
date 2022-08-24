#pragma once
#include "../Core/BaseActor.h"

class Ball : public BaseActor
{
public:
    Ball(int x_axis, int y_axis, bool tickEnabled);

    void tick() override;
    void changeDirection(BaseActor* actor);
    void reset(int x, int y);
    void setPosition(int get_x_axis, int get_x_axis1);
    int y_speed_ = -1;
    int x_speed_ = -1;
};
