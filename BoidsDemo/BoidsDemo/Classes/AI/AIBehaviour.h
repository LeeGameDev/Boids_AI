/*! \file AIBehaviour.h */

#ifndef __AI_BEHAVIOUR_H__
#define __AI_BEHAVIOUR_H__

#include "cocos2d.h"
#include "SpeciesEntity.h"

/*! \class AIBehaviour

	\brief Controls a SpeciesEntity via its steering forces.

	Base class for an AI behaviour that controls an entity via steering forces.
*/
class AIBehaviour
{
public:
	AIBehaviour();
	virtual ~AIBehaviour();

	/*! \brief Computes the steering force to apply to the SpeciesEntity.
		
		\param entity The SpeciesEntity with which to apply behaviour.
		\param nearbyEntities The other SpeciesEntity nearby.
		\param slotsUsed Optimization technique to prevent add/remove calls on std::vector tells the method how many slots of the nearbyEntities are used

		\return The steering force.
	*/
	virtual Vec2 compute(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed) = 0;

	/*! \brief Computes the steering force to apply using Reynold's steering formula.

		\param entity The SpeciesEntity with which to apply steering.
		\param desiredVelocity The desired Velocity to apply.

		\return The steering force to apply.
	*/
	Vec2 applyReynoldsSteering(const SpeciesEntity& entity, Vec2 desiredVelocity) const;

	/*! \brief Gets the enabled state of the AIBehaviour.

		\see setEnabled(bool)

		\return true if the AIBehaviour is enabled, false otherwise.
	*/
	inline bool	isEnabled()	const { return m_IsEnabled; }

	/*! \brief Sets the enabled state of the AIBehaviour.

		\see bool isEnabled()

		\param isEnabled The desired state of the AIBehaviour.
	*/
	inline void	setEnabled(bool isEnabled) { m_IsEnabled = isEnabled; }

	/*! \brief Gets the multiplier to apply to the steering force computed by this AIBehaviour.

		\see setModifier(float)

		\return The modifier value.
	*/
	inline float getModifier() const { return m_Modifier; }

	/*! \brief Sets the multiplier to apply to the steering force computed by this AIBehaviour.

		\see float getModifier()
	
		\param modifier The desired multiplier value.
	*/
	inline void	setModifier(float modifier) { m_Modifier = modifier; }
	
protected:
	bool m_IsEnabled = false;				///< The enabled state of the AIBehaviour (false means the AIBehaviour will not update).
	float m_Modifier = 1.0f;				///< The multiplier to apply to the steering force.
	Vec2 m_DesiredVelocity = Vec2::ZERO;	///< Caches The desired velocity.
};

#endif __AI_BEHAVIOUR_H__