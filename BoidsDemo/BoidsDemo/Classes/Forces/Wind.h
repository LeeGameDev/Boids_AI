/*! \file Wind.h */

#ifndef __WIND_H__
#define __WIND_H__

#include "Force.h"
#include "SpeciesEntity.h"

/*! \class Wind

	\brief Applies a force in one direction to all SpeciesEntity.

	An external force that is applied to all entities of a Flock.
*/
class Wind : public Force
{
public:
	/*! \brief Constructor for a fully defined Wind force.
	
		\param velocity The wind velocity.
	*/
	Wind(Vec2 velocity);

	Wind();
	~Wind();

	/*! \brief Computes the Force applied by the wind on the SpeciesEntity.
	
		\param entity The SpeciesEntity with which to apply the force.

		\return The steering force of the wind.
	*/
	Vec2 computeForceApplied(SpeciesEntity* entity);

	/*! \brief Gets the velocity of the wind.
	
		\return The wind velocity.
	*/
	inline const Vec2 getVelocity() const { return m_Velocity; }
private:
	Vec2 m_Velocity;	// Wind velocity
};

#endif __WIND_H__