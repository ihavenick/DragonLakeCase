#pragma once

class Sprite;

class BaseActor
{

protected:
    Sprite* actor_sprite_ = nullptr;

    bool tickEnabled_ = false;
    int x_axis_ = 0;
    int y_axis_ = 0;
    int tag_;
public:
    static BaseActor* create(int);

    virtual Sprite* getSprite();
    virtual bool init();
    virtual void reset();
    void drawActor() const;
    int getTag();
    BaseActor(int x_axis, int y_axis, bool tickEnabled);
    virtual void tick();
    virtual ~BaseActor();
    bool doCollideWith(const BaseActor* base_actor) const;
    int getXAxis() const;
    int getYAxis() const;
    virtual void Collided();
};
