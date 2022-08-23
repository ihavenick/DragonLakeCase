#pragma once
#include "../Core/BaseActor.h"

class Ball : public BaseActor
{
public:
    Ball(int x_axis, int y_axis, bool tickEnabled);

    void tick() override;
    int y_speed_ = -1;
    int x_speed_ = -1;
};
