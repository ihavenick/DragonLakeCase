#pragma once
#include <list>

#include "BaseActor.h"

class Player;

class GameInstance
{
private:
    int blockCount;
    std::list<BaseActor*> tickActors_;
    static GameInstance* _instance;
    Player* _player;
    class Ball* _ball;
    
public:
    Player* getPlayer() const;
    void SpawnBlocks();
    void beginPlay();
    void SpawnBall();
    static GameInstance* getInstance();
    void tick();
    void setBlockCount(int i);
};
