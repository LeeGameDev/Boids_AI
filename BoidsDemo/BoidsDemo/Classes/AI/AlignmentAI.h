/*! \file AlignmentAI.h */

#ifndef __ALIGNMENT_AI_H__
#define __ALIGNMENT_AI_H__

#include "AIBehaviour.h"

/*! \class AlignmentAI

	\brief SpeciesEntity tend to steer in similar directions.

	An AIBehaviour that defines how entities tend to steer in similar directions as the Flock.
*/
class AlignmentAI : public AIBehaviour
{
public:
	/*! \brief Constructor for a fully defined AlignmentAI behaviour.
	
		\param isEnabled The desired state of the AlignmentAI.
		\param modifier The desired multiplier value.
	*/
	AlignmentAI(bool isEnabled, float modifier);

	AlignmentAI();
	virtual ~AlignmentAI();

	/*! \brief Computes the steering force to apply to the SpeciesEntity.

	\param entity The SpeciesEntity with which to apply behaviour.
	\param nearbyEntities The other SpeciesEntity nearby.
	\param slotsUsed Optimization technique to prevent add/remove calls on std::vector tells the method how many slots of the nearbyEntities are used

	\return The steering force.
	*/
	Vec2 compute(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed);
};

#endif __ALIGNMENT_AI_H__