#pragma once
#include <chrono>
#include <list>

#include "BaseActor.h"

class Player;
class Ball;

class GameInstance
{
private:
    int redblockCount_;
    int blockCount;
    std::list<BaseActor*> tickActors_;
    static GameInstance* _instance;
    Player* _player;
    int playerLives_ = 5;
    bool _gameOver = false;
    BaseActor* _gameOverActor;
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    int randomBuffTime = 60;
    int weakBlockCount_ = 0;
    int ballCount_ = 0;
    std::list<Ball*> ballList_;
    int redBlockLimit = 6;
    
public:
    const BaseActor* getPlayer() const;
    void SpawnBlocks();
    void createPlayer();
    void beginPlay();
    bool CanAbleToSpawnRedBlocks();
    void SpawnBall(bool cond);
    void ballOutofScreen(Ball* ball);
    static GameInstance* getInstance();
    void tick();
    void removeFromScreen(BaseActor* actor);
    void setBlockCount(int i, bool is_powerfull);
    int getWeakBlockCount() const;
    Ball* getBall() const;
};
