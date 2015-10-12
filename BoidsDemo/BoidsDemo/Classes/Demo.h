/*! \file Demo.h */

#ifndef __DEMO_H__
#define __DEMO_H__

#include "cocos2d.h"
#include "Flock.h"

/*! \class Demo

	\brief Instantiates, displays, and runs the Flock.
	
	Runs the demonstration of the Flock moving via steering forces.
*/
class Demo : public cocos2d::Layer
{
public:
    // There's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	Flock* m_Flock; ///< The flock to demo

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	/*! \brief Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".

		\param dt In seconds.
	*/
	virtual void update(float dt);
    
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Demo);

private:
	cocos2d::Vec2 m_Origin;		// Viewport origin
	cocos2d::Label* m_LblDemo;	// Main label
};

#endif // __DEMO_H__