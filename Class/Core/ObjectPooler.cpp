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
    _blockList.clear();
}


BaseActor* ObjectPooler::getAgent(int atag)
{
    if ((atag == 1 && _buffList.empty()) 
            || (atag == 0 && _blockList.empty()))
    {
        return BaseActor::create(atag);
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
    if (object->getTag() == 1) 
    {
        _buffList.push_back(object);
    }
    else if (object->getTag() == 0)
    {
        _blockList.push_back(object);
        object->reset();
    }
    
}