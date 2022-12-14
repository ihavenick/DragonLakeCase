#include "ObjectPooler.h"

#include "BaseActor.h"

ObjectPooler* ObjectPooler::_Instnce = nullptr;


ObjectPooler* ObjectPooler::getInstance()
{
    if (_Instnce == nullptr) {
        _Instnce = new ObjectPooler;
    }
    return _Instnce;
}

void ObjectPooler::reset()
{
    _blockList.clear();            // clear lists (do it better if we dont ?)
    _ballList.clear();
    _buffList.clear();
}


BaseActor* ObjectPooler::getAgent(int atag)
{
    if ((atag == 1 && _buffList.empty()) 
            || (atag == 0 && _blockList.empty())
            || (atag == 2 && _ballList.empty()) ) 
    {
        return BaseActor::create(atag); // create a new one if there is no available one
    }

    if (atag == 2)                                // if we have in pool
    {
       
        BaseActor* resource = _ballList.front();  // get the first one in the list
        _ballList.pop_front();                    // remove it from the list
       
        return resource;                        // return it
    }
    
    if (atag == 1) 
    {
       
        BaseActor* resource = _buffList.front();
        _buffList.pop_front();
       
        return resource;
    }
    if (atag == 0)
    {
        BaseActor* resource = _blockList.front();
        _blockList.pop_front();
        
        return resource;
    }
}


void ObjectPooler::returnAgent(BaseActor* object)
{
    if (object->getTag() == 1)                // add to pool if we dont need now but will need it later
    {
        _buffList.push_back(object);
        object->reset();
    }
    else if (object->getTag() == 0)
    {
        _blockList.push_back(object);
        object->reset();
    }
    else
    {
        _ballList.push_back(object);
        object->reset();
    }
    
}