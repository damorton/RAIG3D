#ifndef HELLOWORLD_SCENE_H_
#define HELLOWORLD_SCENE_H_

#include "../cocos2d/cocos/cocos2d.h"
#include <vector>
#include "raig/raig_client.h"

class Vector3;

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

    raig::Raig *m_RaigAI;

    std::vector<std::shared_ptr<Vector3> > m_vPath;

    int m_iGameWorldSize;

    int m_iStartX;
    int m_iStartZ;
    int m_iGoalX;
    int m_iGoalZ;
};

#endif // __HELLOWORLD_SCENE_H__
