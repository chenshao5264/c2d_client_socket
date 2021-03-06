#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "LoginScene.h"

#include "ClientNet/Socket/TCPManager.h"

#include "CCEx/EventDispatcherEx.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem1 = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem1->setPosition(Vec2(origin.x + visibleSize.width - closeItem1->getContentSize().width/2 ,
                                origin.y + closeItem1->getContentSize().height/2));


    auto closeItem2 = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem2->setPosition(Vec2(origin.x + visibleSize.width - closeItem2->getContentSize().width / 2,
        origin.y + closeItem2->getContentSize().height / 2 + 100));

    auto closeItem3 = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem3->setPosition(Vec2(origin.x + visibleSize.width - closeItem3->getContentSize().width / 2,
        origin.y + closeItem3->getContentSize().height / 2 + 200));


    closeItem1->setTag(1);
    closeItem2->setTag(2);
    closeItem3->setTag(3);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem1, closeItem2, closeItem3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    TCPManager::getInstance()->makeConnect1("127.0.0.1", 3000);
    

    EventDispatcherEx::getInstance()->addCustomEventListener(this, e_do_demo_after, [=](cocos2d::EventCustom* evt)
    {
        CCLOG("do_demo_after");
    });


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{

    auto btn = dynamic_cast<MenuItem*>(pSender);
    if (btn->getTag() == 1)
    {
        CCLOG("1111");
        TCPManager::getInstance()->sendLoginReq();
    }
    else if(btn->getTag() == 2)
    {
        CCLOG("2222");
        EventDispatcherEx::getInstance()->removeEventListenerForTarget(this);
    }
    else if (btn->getTag() == 3)
    {
        auto scene = LoginScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }

    
   
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
}

void HelloWorld::onExit()
{
    EventDispatcherEx::getInstance()->removeEventListenerForTarget(this);
    Layer::onExit();
}
