/*! \file SeparationAI.h */

#ifndef __SEPARATION_AI_H__
#define __SEPARATION_AI_H__

#include "AIBehaviour.h"

/*! \class SeparationAI

	\brief SpeciesEntity of a Flock tend to steer away from other SpeciesEntity when they are too close.

	An AIBehaviour that defines how entities tend to steer away from other entities when they are too close.
*/
class SeparationAI : public AIBehaviour
{
public:
	/*! \brief Constructor for a fully defined SeparationAI behaviour.

		\param isEnabled The desired state of the AlignmentAI.
		\param modifier The desired multiplier value.
	*/
	SeparationAI(bool isEnabled, float modifier);

	SeparationAI();
	virtual ~SeparationAI();

	/*! \brief Computes the steering force to apply to the SpeciesEntity.

	\param entity The SpeciesEntity with which to apply behaviour.
	\param nearbyEntities The other SpeciesEntity nearby.
	\param slotsUsed Optimization technique to prevent add/remove calls on std::vector tells the method how many slots of the nearbyEntities are used

	\return The steering force.
	*/
	Vec2 compute(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed);
};

#endif __SEPARATION_AI_H__