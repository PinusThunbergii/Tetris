#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class StartScene: public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);

    void onClick(Ref* pSender);
private:

protected:

};
