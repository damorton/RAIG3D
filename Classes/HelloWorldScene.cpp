#include "HelloWorldScene.h"

#include <time.h>

USING_NS_CC;

Scene* HelloWorldScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorldScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance

bool HelloWorldScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size winSize = Director::getInstance()->getWinSize();

    // Perspective camera
    //auto s = Director::getInstance()->getWinSize();
    auto camera = Camera::createPerspective(60, (GLfloat) visibleSize.width / visibleSize.height, 1, 10000);

    // Set camera position and look direction. The cameras flag must also
    // be set different to DEFAULT in order to filter out the main cameras
    // rendering references.
    camera->setPosition3D(Vec3(0, 1000, 1400));
    camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);

    // 3D Sprite
    auto orc = cocos2d::Sprite3D::create("orc.c3b");

    // Scale sprite
    float orcScaleFactor = 1.0f;
    orc->setScale((winSize.width / winSize.height) * orcScaleFactor);

    orc->setPosition3D(Vec3(0, 0, 0));
    orc->setRotation3D(Vec3(0, 180, 0));
    orc->setGlobalZOrder(1);
    std::string filenameOrc = "orc.c3b";
    auto animation = Animation3D::create(filenameOrc);
    if (animation) {
        auto animate = Animate3D::create(animation);
        auto repeat = RepeatForever::create(animate);
        orc->runAction(repeat);
    }
    this->addChild(orc);

    // Tiled map .tmx
    m_TiledMap = new TMXTiledMap();
    m_TiledMap->initWithTMXFile("tiledMap.tmx");
    m_BackgroundLayer = m_TiledMap->getLayer("Background");
    Size mapSize = m_TiledMap->getMapSize();
    Size tileSize = m_TiledMap->getTileSize();
    //m_TiledMap->setPosition3D(Vec3(-(mapSize.width * tileSize.width / 2), 0, (mapSize.width * tileSize.width / 2)));
    m_TiledMap->setAnchorPoint(Vec2(0.5, 0.5));
    m_TiledMap->setPosition3D(Vec3(0, 0, 0));
    m_TiledMap->setRotation3D(Vec3(-90, 0, 0));

    // Scale tilemap
    float tilemapScaleFactor = 1.0f;
    m_TiledMap->setScale((winSize.width / winSize.height) * tilemapScaleFactor);

    this->addChild(m_TiledMap);

    // Set camera mask to only render new camera objects
    this->setCameraMask(2);

    // Create RAIG and connect to remote server
    m_RaigAI = new raig::RaigClient();
	std::shared_ptr<std::string> ipAddress(new std::string("192.168.1.100"));
	std::shared_ptr<std::string> service(new std::string("27000"));
	m_RaigAI->InitConnection(ipAddress, service);
    //m_RaigAI->InitConnection("127.0.0.1", "27000");
    //m_RaigAI->InitConnection("damortonpi.duckdns.org", "27000");

    // Send RAIG the size of the game world and type of service being
    auto layerSize = m_BackgroundLayer->getLayerSize();
    m_iGameWorldSize = layerSize.width - 1;
    m_RaigAI->CreateGameWorld(layerSize.width, raig::RaigClient::ASTAR);

    // Create obstacles in the game world by blocking off some of the cells on the RAIG grid
    // Read the tilemap properties and check if each cell is blocked or open
    for (int x = 0; x < layerSize.width; ++x)
    {
        for (int z = 0; z < layerSize.height; ++z)
        {
        	int gid = m_BackgroundLayer->getTileGIDAt(Vec2(x, z));
        	if(gid)
        	{
        		ValueMap properties = m_TiledMap->getPropertiesForGID(gid).asValueMap();
        		if (!properties.empty()) {
					std::string blocked = properties["Blocked"].asString();
					if ("True" == blocked) {
						// Send blocked cell to RAIG
						m_RaigAI->SetCellBlocked(base::Vector3(x, 0, z));
					}
				}
        	}
        }
    }

	//m_RaigAI->SetCellOpen(Vector3(0, 0, 0));

	LogFile.open("c:\\Logfile.txt");
	LogFile << "Init" << std::endl;
	LogFile.close();

	// Find a path through the game world
    m_RaigAI->FindPath(new base::Vector3(0, 0, 0), new base::Vector3(m_iGameWorldSize, 0, m_iGameWorldSize));

    srand(time(0));

    this->scheduleUpdate();
    return true;
}

void HelloWorldScene::update(float dt)
{
	m_RaigAI->Update();

	// Get the path processed by the remote service
	//m_RaigAI->GetPath();

	if(!m_RaigAI->GetPath().empty())
	{
		// Once RAIG has returned a path loop the vector and color the cells in the path
		pathColorR = rand() % (255 + 1 - 0) + 0;
		pathColorG = rand() % (255 + 1 - 0) + 0;
		pathColorB = rand() % (255 + 1 - 0) + 0;

		for(auto node = m_RaigAI->GetPath().begin(); node != m_RaigAI->GetPath().end(); ++node)
		{
			//m_BackgroundLayer->getTileAt(Vec2((*node)->m_iX, (*node)->m_iZ))->setColor(Color3B(pathColorR, pathColorG, pathColorB));
			int x = (*node)->m_iX;
			int z = (*node)->m_iZ;
			auto tile = m_BackgroundLayer->getTileAt(Vec2(x, z));
			tile->setColor(Color3B(pathColorR, pathColorG, pathColorB));
		}

		m_RaigAI->GetPath().clear();
	}



	// rand() % (max_number + 1 - minimum_number)) + minimum_number;
	m_iStartX = rand() % (m_iGameWorldSize + 1 - 0) + 0;
	m_iStartZ = rand() % (m_iGameWorldSize + 1 - 0) + 0;
	m_iGoalX = rand() % (m_iGameWorldSize + 1 - 0) + 0;
	m_iGoalZ = rand() % (m_iGameWorldSize + 1 - 0) + 0;

	m_RaigAI->FindPath(new base::Vector3(m_iStartX, 0, m_iStartZ), new base::Vector3(m_iGoalX, 0, m_iGoalZ));
}

void HelloWorldScene::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
