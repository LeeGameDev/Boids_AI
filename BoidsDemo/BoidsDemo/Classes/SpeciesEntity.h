/*! \file SpeciesEntity.h */

#ifndef __SPECIES_ENTITY_H__
#define __SPECIES_ENTITY_H__

#include "cocos2d.h"
#include "Species.h"

USING_NS_CC;

/*! \class SpeciesEntity

	\brief An entity to be used in a flocking algorithm.

	An entity with a Species type and representation to be used in a flocking algorithm.
*/
class SpeciesEntity : public cocos2d::Node
{
public:
	/*! \brief Allocates and initializes a node.

		\return A initialized node which is marked as "autorelease".
	*/
	CREATE_FUNC(SpeciesEntity);

	/*! \brief Initializes the entity with a Species type.

		\param type Is the Species type.

		\return true if the initialization was successful, false otherwise.
	*/
	bool initWithSpecies(const Species& type);

	/*! \brief Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".

		\param dt In seconds.
	*/
	virtual void update(float dt);

	/*! \brief Sets the velocity (x,y) of the SpeciesEntity.

		\see const Vec2& getVelocity()

		\param v The velocity.
	*/
	inline void setVelocity(const Vec2& v) { m_Velocity = v; }

	/*! \brief Sets the acceleration (x,y) of the SpeciesEntity.

		\see const Vec2& getAcceleration()

		\param a The acceleration.
	*/
	inline void setAcceleration(const Vec2& a) { m_Acceleration = a; }

	/*! \brief Computes the heading of the entity based on its velocity.

		\return The heading in degrees.
	*/
	inline float getHeading() const	{
		Vec2 direction = m_Velocity.getNormalized();
		return CC_RADIANS_TO_DEGREES(Vec2(direction.x, -direction.y).getAngle());
	}

	/*! \brief Gets the velocity (x,y) of the SpeciesEntity.

		\see setVelocity(const Vec2&)

		\return The velocity.
	*/
	inline const Vec2& getVelocity() const { return m_Velocity; }

	/*! \brief Gets the acceleration (x,y) of the SpeciesEntity.

		\see setAcceleration(const Vec2&)
		
		\return The acceleration.
	*/
	inline const Vec2& getAcceleration() const { return m_Acceleration;	}

	/*! \brief Gets the Species type of the SpeciesEntity.

		\see bool initWithSpecies(const Species&)

		\return The Species type.
	*/
	inline const Species* getSpecies() const { return m_Species; }

	/*! \brief Gets the Sprite of the SpeciesEntity.

		\return The Sprite.
	*/
	inline const Sprite* getSprite() const { return m_Sprite; }

	/*! \brief a selector callback */
	void menuCloseCallback(Ref* pSender);

private:
	float m_Heading = 0.0f;				// The heading of the SpeciesEntity based on its velocity
	Vec2 m_Velocity = Vec2::ZERO;		// The velocity of the SpeciesEntity modifies its position
	Vec2 m_Acceleration = Vec2::ZERO;	// The acceleration of the SpeciesEntity modifies its velocity
	const Species* m_Species;			// The Species holds all the data regarding what type the SpeciesEntity is
	Sprite*	m_Sprite;					// The heading of the SpeciesEntity based on its velocity
};

#endif __SPECIES_ENTITY_H__