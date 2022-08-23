#pragma once
#include "../Core/BaseActor.h"

class Block : public BaseActor
{
public:
    Block( int x_axis, int y_axis, bool tickEnabled);

    bool init(int blockType);
    void reset() override;
    void tick() override;
    void setPosition(int x, int y);
};
