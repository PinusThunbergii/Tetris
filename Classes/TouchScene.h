#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class TouchScene: public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    CREATE_FUNC(TouchScene)
private:
    Label* labelTouchInfo;
protected:

};

