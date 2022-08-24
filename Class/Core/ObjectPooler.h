#include <list>

class BaseActor;

class ObjectPooler
{
private:
    ObjectPooler() {}

public:
    static ObjectPooler* getInstance();
    void reset();
    BaseActor* getAgent(int);
    void returnAgent(BaseActor*);

private:
    static ObjectPooler* _Instnce;
    std::list<BaseActor*> _blockList;
    std::list<BaseActor*> _buffList;
    std::list<BaseActor*> _ballList;
};
