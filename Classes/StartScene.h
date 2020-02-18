#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class StartScene: public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);
private:

protected:

};
