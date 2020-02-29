#include "StartScene.h"

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    isFullScreen = false;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    screenSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto label = Label::createWithTTF("Tetris", "fonts/Marker Felt.ttf", 60);
    label->setTextColor(Color4B::RED);
    label->setAnchorPoint(Vec2(0, 0));
    float offset = 10.0f;
    Vec2 pos = Vec2(visibleSize.width / 2.0f - label->getContentSize().width / 2,
                    visibleSize.height - label->getContentSize().height / 2 - offset);
    label->setPosition(pos);
    this->addChild(label, 1);
    auto button = ui::Button::create();
    button->setTitleText("Click");
    button->setPosition(Vec2(100, 100));

    //http://www.pixnbgames.com/blog/c/how-to-add-event-listener-to-button-cocos2d-x-3-and-cpp/
    //button->addClickEventListener(CC_CALLBACK_1(StartScene::onClick, this));
    button->addTouchEventListener(CC_CALLBACK_2(StartScene::onClick, this));

    this->addChild(button);

    Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    //polygonInfo.setRect(Rect(0, 0, 40, 40));
    //sprite = Sprite::create("sprites/bird.png", Rect(center, Size(40, 40)));
    sprite = Sprite::create("sprites/bird.png");
    //auto pinfo = AutoPolygon::generatePolygon("sprites/bird.png");
    //sprite = Sprite::create(pinfo);
   
    //auto rt = RenderTexture::create(100, 100);
    //rt->begin();
    //sprite->visit();
    //rt->end();
    //sprite->removeFromParent();
    //CC_SAFE_RELEASE(sprite);
    //sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());

    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprite->setContentSize(Size(40, 40));
    sprite->setScale(1.0f);
    sprite->setPosition(center);

    this->addChild(sprite, -2);

    //dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView())->setCursorVisible(true);

    //checkBox = CheckBox::create("icons/check_blank.png", "icons/check.png");
    checkBox = CheckBox::create("icons/CheckBox_Normal.png", 
                                "icons/CheckBox_Press.png",
                                "icons/CheckBoxNode_Normal.png", 
                                "icons/CheckBoxNode_Disable.png", 
                                "icons/CheckBox_Disable.png");

    checkBox->addTouchEventListener(CC_CALLBACK_2(StartScene::toggleCheckbox, this));
    checkBox->setPosition(Vec2(center.x, 100));
    //checkBox->setScale(0.2);
    this->addChild(checkBox, -1);

    this->scheduleUpdate();
    return true;
}

Scene* StartScene::createScene()
{
    return StartScene::create();
}

void StartScene::onClick(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        /* code */
        break;
    case Widget::TouchEventType::ENDED:
    {
        CCLOG("CLICK");
        sprite->setRotation(sprite->getRotation() + 10.0f);
        sprite->setScale(sprite->getScale() + 0.1f);
        auto mv = MoveBy::create(2, Vec2(100.0f, 100.0f));
        auto mv1 = MoveBy::create(2, Vec2(-100.0f, -100.0f));
        auto delay = DelayTime::create(1);
        auto mv2 = RotateBy::create(1, 135.0f);
        auto seq = Sequence::create(mv, delay, mv2, mv1, nullptr);
        sprite->runAction(seq);
        break;
    }
        
    case Widget::TouchEventType::CANCELED:
        /* code */
        break;
    case Widget::TouchEventType::MOVED:
        /* code */
        break;
    default:
        break;
    }
}

void StartScene::update(float dt)
{
    std::cout << "Update! " << dt << std::endl;
}

void StartScene::toggleCheckbox(Ref* pSender, Widget::TouchEventType type)
{
    std::cout << "checkbox" << std::endl;
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        /* code */
        break;
    case Widget::TouchEventType::ENDED:
    {
        isFullScreen = !isFullScreen;
        if(isFullScreen)
            dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView())->setFullscreen();
        else
            dynamic_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView())->setWindowed(screenSize.width, screenSize.height);
        break;
    }
        
    case Widget::TouchEventType::CANCELED:
        /* code */
        break;
    case Widget::TouchEventType::MOVED:
        /* code */
        break;
    default:
        break;
    }
}
