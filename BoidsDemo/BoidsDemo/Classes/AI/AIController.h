/*! \file AIController.h */

#ifndef __AI_CONTROLLER_H__
#define __AI_CONTROLLER_H__

#include "AI\AIBehaviour.h"
#include "Forces\Force.h"
#include "SpeciesEntity.h"
#include <vector>

/*! \class AIBehaviour */
class AIBehaviour;

/*! \class AIController

	\brief Controls a SpeciesEntity by applying its AIbehaviours and external forces.

	AIController handles how a SpeciesEntity moves in a flock via behaviours and external forces.
*/
class AIController
{
public:
	std::vector<AIBehaviour*> behaviours;	///< All AIBehaviours to apply to the Flock
	std::vector<Force*> externalForces;		///< All external Forces to apply to the Flock

	AIController();
	virtual ~AIController();

	/*! \brief Applies both AIBehaviour and Force forces to the SpeciesEntity.

		\param entity The SpeciesEntity with which to apply all forces.
		\param nearbyEntities The other SpeciesEntity nearby.
		\param slotsUsed Optimization technique to prevent add/remove calls on std::vector tells the method how many slots of the nearbyEntities are used
	*/
	void applyAllForces(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed);

	/*! \brief Gets the enabled state of the AIController.

		\see setEnabled(bool)

		\return true if the AIController is enabled, false otherwise.
	*/
	inline bool isEnabled() const { return m_Enabled; }

	/*! \brief Sets the enabled state of the AIController.

		\see bool isEnabled()

		\param isEnabled The desired state of the AIController.
	*/
	inline void setEnabled(bool const isEnabled) { m_Enabled = isEnabled; }

protected:
	std::string	m_Name = "AI Controller";	///< AIController name.
	bool m_Enabled = false;					///< The enabled state of the AIController (false means the AIController will not update).
	Vec2 m_SteeringForce = Vec2::ZERO;		///< Caches The desired velocity.
};

#endif __AI_CONTROLLER_H__