﻿#include "GameInstance.h"

#include <chrono>

#include "ObjectPooler.h"
#include "../../game.h"
#include "../Block/Block.h"
#include "../Player/Player.h"
#include "../Ball//Ball.h"

class Player;


GameInstance* GameInstance::_instance = nullptr;

GameInstance* GameInstance::getInstance() {
    if (_instance == nullptr) {
        _instance = new GameInstance();
    }
    return _instance;
}

const BaseActor* GameInstance::getPlayer() const
{
    return _player;
}

void GameInstance::SpawnBlocks()
{
    int visibleSizeWidth, visibleSizeHeight;
    MyFramework::getScreenSizeFromFramework(visibleSizeWidth, visibleSizeHeight);
    int originY = 0;

    //creating block for getting its size. yeah its not great way but it makes it %100 accurate :D
    const auto block = new Block(0, 0, true);

    const auto marginx = 30.f;
    int blockWidth = 0;
    int unnecessary = 0;
    MyFramework::getSpriteSizeInFramework(block->getSprite(), blockWidth, unnecessary);


    const float deltaValue = visibleSizeWidth - marginx / 1.5f;
    const int colonBlockCount = (deltaValue / blockWidth + 1) / 0.4f;

    int BlockCount = 0;
    for (int j = 0; j < colonBlockCount; j++)
        for (int i = 0; i < colonBlockCount; i++)
        {
            const auto block = dynamic_cast<Block*>(ObjectPooler::getInstance()->getAgent(0));
            if (block == nullptr)
                printf("error getting block from pool");
            else
            {
                BlockCount++;
                (block->getIsPowered() ? redblockCount_ : weakBlockCount_)++;
                
                block->setPosition((visibleSizeWidth / 4) + (visibleSizeWidth - deltaValue) + (marginx + 50) * i,
                                   originY + 50 * j);

                this->tickActors_.push_back(block);
            }
        }

    
    setBlockCount(+BlockCount, true);
    //setting enemy count to track enemies and not to check its count on update to regenerate enemies
    delete block;
}

void GameInstance::createPlayer()
{
    int w, h;
    int spriteW, spriteH;
    MyFramework::getScreenSizeFromFramework(w, h );
    
    Sprite* test = MyFramework::createSpriteInFramework("data/49-Breakout-Tiles.png");
   
    MyFramework::getSpriteSizeInFramework(test,spriteW,spriteH);
    MyFramework::setSpriteSizeInFramework(test,spriteW/6,spriteH/10);
    MyFramework::getSpriteSizeInFramework(test,spriteW,spriteH);
    _player = new Player(w/2 - (spriteW /2),h - spriteH,true);
    _player->init(test);
}

void GameInstance::beginPlay()
{
    createPlayer();

    tickActors_.push_back(_player);
    SpawnBlocks();

    _startTime = std::chrono::system_clock::now();
    randomBuffTime = rand() % 60 + 1;
}

bool GameInstance::CanAbleToSpawnRedBlocks()
{
    return  !(redblockCount_ >= redBlockLimit);
}

void GameInstance::SpawnBall(bool isBuff)
{
    if(isBuff)
    {
        const auto _ball = getBall();
        if(_ball == nullptr)
            return;

        
        //split ball into two balls
        for(int i = 0; i < 2; i++)
        {
            const auto ball = dynamic_cast<Ball*>(ObjectPooler::getInstance()->getAgent(2));
            if (ball == nullptr)
                printf("error getting ball from pool");
            else
            {
                ball->setPosition(_ball->getXAxis(), _ball->getYAxis());
                ball->x_speed_ = _ball->x_speed_ * -1;
                if(i==1)
                    ball->y_speed_ = _ball->y_speed_ * -1;
            
                this->tickActors_.push_back(ball);
                this->ballList_.push_back(ball);
            }
        }
       
    }
    else
    {
        auto _ball = new Ball(_player->getXAxis(), _player->getYAxis() - 20,true);
        
        tickActors_.push_back(_ball);
        ballList_.push_back(_ball);
    }
   
}

void GameInstance::ballOutofScreen(Ball* ball)
{

    if(!ballList_.empty())
    {
        ballList_.remove(ball);
        tickActors_.remove(ball);
        ObjectPooler::getInstance()->returnAgent(ball);
        
        return;
    }
  

    
    if(playerLives_ > 0)
    {
        
        playerLives_--;
    }
    else
    {
        if(_gameOver)
            return;
        
        _gameOver=true;
       tickActors_.empty();
        _gameOverActor = BaseActor::create(4);
    }
}

void GameInstance::tick()
{
    if(_gameOver)
    {
        if(_gameOverActor)
            _gameOverActor->drawActor();
    }
    else if(!tickActors_.empty())
    {
        const auto cacheList = tickActors_;
        const auto cacheBallList = ballList_;
        
        for(const auto actor : cacheList)
        {
            actor->tick();

            for(const auto ball : cacheBallList)
            {
                if(actor != ball && actor->getTag() != 3 && actor->doCollideWith(ball))
                {
                    ball->changeDirection(actor);
                    actor->Collided();
                }
            }
        }

        
       

        const auto end = std::chrono::system_clock::now();

        const std::chrono::duration<double> elapsed_seconds = end-_startTime;

        if(elapsed_seconds.count() >= randomBuffTime)
        {
            _startTime = std::chrono::system_clock::now();
            randomBuffTime = rand() % 60 + 1;
            
            BaseActor* buff = ObjectPooler::getInstance()->getAgent(1);
            if(buff)
            {
                tickActors_.push_back(buff);
            }
        }
    }
    
}

void GameInstance::removeFromScreen(BaseActor* actor)
{
    if(actor)
    {
        tickActors_.remove(actor);
        ObjectPooler::getInstance()->returnAgent(actor);
    }
}

void GameInstance::setBlockCount(int i, bool is_powerfull)
{
    blockCount += i;

    if(!is_powerfull)
        weakBlockCount_ += i;
        
    if (blockCount == 0) //SETS BLOCK COUNT IF THERE IS NO BLOCK LEFT REGENERATES THEM 
    {
        //win
        printf("you win");
        BaseActor* winActor = BaseActor::create(5);
        
        tickActors_.push_back(winActor);
    }
}

int GameInstance::getWeakBlockCount() const
{
    return weakBlockCount_;
}

Ball* GameInstance::getBall() const
{
    if(!ballList_.empty())
        return ballList_.front();
    return nullptr;
}
