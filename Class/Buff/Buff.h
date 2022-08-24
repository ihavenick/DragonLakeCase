#pragma once
#include "../Core/BaseActor.h"

class Buff : public BaseActor
{
private:
    bool isPositive;
    
public:
    Buff(int x_axis, int y_axis, bool tickEnabled);
    void tick() override;
    void init(int is_positive);
};
