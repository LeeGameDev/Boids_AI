/*! \file CohesionAI.h */

#ifndef __COHESION_AI_H__
#define __COHESION_AI_H__

#include "AIBehaviour.h"

/*! \class CohesionAI

	\brief SpeciesEntity tend to steer towards the centre of mass of a Flock.

	An AIBehaviour that defines how entities tend to steer towards the centre of mass of a Flock.
*/
class CohesionAI: public AIBehaviour
{
public:
	/*! \brief Constructor for a fully defined CohesionAI behaviour.
	
		\param isEnabled The desired state of the AlignmentAI.
		\param modifier The desired multiplier value.
	*/
	CohesionAI(bool isEnabled, float modifier);

	CohesionAI();
	virtual ~CohesionAI();

	/*! \brief Computes the steering force to apply to the SpeciesEntity.

	\param entity The SpeciesEntity with which to apply behaviour.
	\param nearbyEntities The other SpeciesEntity nearby.
	\param slotsUsed Optimization technique to prevent add/remove calls on std::vector tells the method how many slots of the nearbyEntities are used

	\return The steering force.
	*/
	Vec2 compute(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed);
};

#endif __COHESION_AI_H__