#include "Demo.h"

#define randFloatX (CCRANDOM_0_1() * (visibleSize.width * 0.5f))
#define randFloatY (CCRANDOM_0_1() * (visibleSize.height * 0.5f))

USING_NS_CC;

/*
TODO:
* Stretch Goal: 1000 entities at 60fps (current achievement 900)
* Cleanup/Polish
*/

Scene* Demo::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Demo::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Demo::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	m_Origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(Demo::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(m_Origin.x + visibleSize.width - closeItem->getContentSize().width * 0.5f,
		m_Origin.y + closeItem->getContentSize().height * 0.5f));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);

	m_LblDemo = Label::createWithTTF("Boids Demo", "fonts/Marker Felt.ttf", 24);
	addChild(m_LblDemo);
    
	m_LblDemo->setPosition(Vec2(m_Origin.x + visibleSize.width * 0.5f,
		m_Origin.y + visibleSize.height - m_LblDemo->getContentSize().height));

	srand(time(0));
	m_Flock = new Flock("FlockBoid.xml");
	SpeciesEntity* boid;
	float posXOffset = visibleSize.width * 0.25f;
	float posYOffset = visibleSize.height * 0.25f;
	for (int i = 0; i < m_Flock->getSize(); i++) {
		boid = m_Flock->boids[i];
		boid->initWithSpecies(*m_Flock->getSpecies());
		addChild(boid, 0);
		boid->setPosition(randFloatX + posXOffset, randFloatY + posYOffset);
	}
	
	scheduleUpdate();

    return true;
}

void Demo::update(float dt) {
	// Update Flock
	m_Flock->update(dt);
}

void Demo::menuCloseCallback(Ref* pSender) {
	m_Flock->getAIController()->setEnabled(false);
	delete m_Flock;
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}