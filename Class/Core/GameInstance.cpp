#include "GameInstance.h"

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

Player* GameInstance::getPlayer() const
{
    return _player;
}

void GameInstance::SpawnBlocks()
{
    int visibleSizeWidth, visibleSizeHeight;
    MyFramework::getScreenSizeFromFramework(visibleSizeWidth,visibleSizeHeight);
    int originY = 0;

    //creating enemy for getting its size. yeah its not great way but it makes it %100 accurate :D
    const auto e = new Block(0,0,true);
    
    const auto marginx = 30.f;
    int enemywidth = 0;
    int unnecessary = 0;
    MyFramework::getSpriteSizeInFramework(e->getSprite(),enemywidth, unnecessary);
        

    const float deltavalue = visibleSizeWidth - marginx / 1.5f;
    const int colonenemycount = (deltavalue / enemywidth + 1) / 0.4f;
    
    int enemyCount = 0;
    for (int j = 0; j < colonenemycount; j++)
        for (int i = 0; i < colonenemycount; i++)
        {
            const auto enemy = dynamic_cast<Block*>(ObjectPooler::getInstance()->getAgent(0));
            if (enemy == nullptr) 
                printf("error getting enemy");
            else {
                enemyCount++;
               // enemy->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
                enemy->setPosition((visibleSizeWidth/4) +(visibleSizeWidth -deltavalue) + (marginx + 50) * i, 
                                            originY + 50 * j);
                
                this->tickActors_.push_back(enemy);
                
            }
        }
    setBlockCount(+enemyCount);   //setting enemy count to track enemies and not to check its count on update to regenerate enemies
    delete e;
    
}

void GameInstance::beginPlay()
{
    int w, h;
    int sW, sH;
    MyFramework::getScreenSizeFromFramework(w, h );
    
    Sprite* test = MyFramework::createSpriteInFramework("data/49-Breakout-Tiles.png");
   
     MyFramework::getSpriteSizeInFramework(test,sW,sH);
     MyFramework::setSpriteSizeInFramework(test,sW/10,sH/10);
     MyFramework::getSpriteSizeInFramework(test,sW,sH);
    _player = new Player(w/2 - (sW /2),h - sH,true);
    _player->init(test);

    tickActors_.push_back(_player);
    SpawnBlocks();
}

void GameInstance::SpawnBall()
{
    _ball = new Ball(_player->getXAxis(), _player->getYAxis() - 10,true);
    tickActors_.push_back(_ball);
}

void GameInstance::tick()
{
    if(!tickActors_.empty())
    {
        for(const auto actor : tickActors_)
        {
            actor->tick();

            if(actor->getTag() != 3 && _ball)
            {
                 if (actor->doCollideWith(_ball))
                 {
                     tickActors_.remove(_ball);
                     delete _ball;
                 }
            }
        }
    }
}

void GameInstance::setBlockCount(int i)
{
    blockCount += i;
    if (blockCount == 0) //SETS ENEMY COUNT IF THERE IS NO ENEMY LEFT REGENERATES THEM 
    {
        SpawnBlocks();
    }
}
