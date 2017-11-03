#ifndef __LoginScene_SCENE_H__
#define __LoginScene_SCENE_H__

#include "cocos2d.h"

class LoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoginScene);
};

#endif // __HELLOWORLD_SCENE_H__
