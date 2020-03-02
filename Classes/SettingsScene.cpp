#include "SettingsScene.h"
#include "StartScene.h"

bool SettingsScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    view = dynamic_cast<GLViewImpl *>(Director::getInstance()->getOpenGLView());

    closeButton = Button::create("icons/exit_unselected.png", "icons/exit_selected.png");
    closeButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    closeButton->setScale(visibleSize.height / 3000);
    closeButton->setPosition(Vec2(visibleSize.width, 0));
    closeButton->addClickEventListener(CC_CALLBACK_0(onClick_closeButton, this));
    this->addChild(closeButton, -1);

    backButton = Button::create("icons/back.png", "icons/back_selected.png");
    backButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    backButton->setScale(visibleSize.height / 3000);
    backButton->setPosition(Vec2::ZERO);
    backButton->addClickEventListener(CC_CALLBACK_0(onClick_backButton, this));
    this->addChild(backButton, -1);

    settingsMenu = Layer::create();

    auto displayModeLabel = Label::createWithTTF("Fullscreen", "fonts/Marker Felt.ttf", 60);
    displayModeLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

    /*displayModeCheckBox = CheckBox::create("icons/CheckBox_Normal.png",
                                           "icons/CheckBox_Press.png",
                                           "icons/CheckBoxNode_Normal.png",
                                           "icons/CheckBoxNode_Disable.png",
                                           "icons/CheckBox_Disable.png");*/

    displayModeCheckBox = CheckBox::create("icons/check_blank.png",
                                           "icons/check.png");

    displayModeCheckBox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    displayModeCheckBox->setPosition(Vec2(displayModeLabel->getContentSize().width, 0));
    displayModeCheckBox->addTouchEventListener(CC_CALLBACK_2(SettingsScene::onClick_checkBox, this));
    displayModeCheckBox->setSelected(view->isFullscreen());
    //displayModeCheckBox->setSelected(false);
    displayModeCheckBox->setScale(0.1);
    settingsMenu->addChild(displayModeCheckBox, -1);
    settingsMenu->addChild(displayModeLabel);
    settingsMenu->setPosition(center.x, visibleSize.height);
    this->addChild(settingsMenu, -1);

    return true;
}

Scene *SettingsScene::createScene()
{
    return SettingsScene::create();
}

void SettingsScene::onClick_closeButton(Ref *sender)
{
    Director::getInstance()->end();
}

void SettingsScene::onClick_backButton(Ref *sender)
{
    Director::getInstance()->replaceScene(StartScene::create());
}

void SettingsScene::onClick_checkBox(Ref *sender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
    {
        std::cout << "TouchEventType::BEGAN" << std::endl;
        std::cout << displayModeCheckBox->isSelected() << std::endl;
        break;
    }
    case Widget::TouchEventType::ENDED:
    {
        std::cout << "TouchEventType::ENDED" << std::endl;
        //facepalm
        //@$#$#@!!!
        bool isSelected = !displayModeCheckBox->isSelected();
        //displayModeCheckBox->setSelected(isSelected);
        std::cout << displayModeCheckBox->isSelected() << std::endl;
        //if (displayModeCheckBox->isSelected())
        if (isSelected)
        {
            view->setFullscreen();
        }
        else if (view->isFullscreen())
        {
            view->setWindowed(1600, 960);
        }
        break;
    }
    case Widget::TouchEventType::CANCELED:
    {
        std::cout << "TouchEventType::CANCELED" << std::endl;
        std::cout << displayModeCheckBox->isSelected() << std::endl;
        break;
    }
    case Widget::TouchEventType::MOVED:
    {
        std::cout << "TouchEventType::MOVED" << std::endl;
        std::cout << displayModeCheckBox->isSelected() << std::endl;
        break;
    }
    default:
        break;
    }
    
}