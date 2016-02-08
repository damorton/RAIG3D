#ifndef HELLOWORLD_SCENE_H_
#define HELLOWORLD_SCENE_H_

#include <vector>

#include "cocos2d.h"
#include "raig/raig_client.h"
#include <fstream>
#include <iostream>

class HelloWorldScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual ~HelloWorldScene(){};
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorldScene);

    void update(float dt) override;

private:
    cocos2d::TMXTiledMap *m_TiledMap;
    cocos2d::TMXLayer *m_BackgroundLayer;

    raig::RaigClient *m_RaigAI;

    int m_iGameWorldSize;

    int pathColorR;
    int pathColorG;
    int pathColorB;

    int m_iStartX;
    int m_iStartZ;
    int m_iGoalX;
    int m_iGoalZ;
};

#endif // __HELLOWORLD_SCENE_H__
