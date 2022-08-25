#pragma once
#include "../Core/BaseActor.h"

class Block : public BaseActor
{
private:
    int durability_=2;
    bool isPowerfull_=false;
    
public:
    Block( int x_axis, int y_axis, bool tickEnabled);

    bool init(int blockType);
    void reset() override;
    void tick() override;
    void Collided() override;
    bool getIsPowered() const;

    void setPosition(int x, int y);
};
