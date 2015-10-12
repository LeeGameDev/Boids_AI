#include "AlignmentAI.h"

AlignmentAI::AlignmentAI(bool isEnabled, float modifier) {
	m_IsEnabled = isEnabled;
	m_Modifier = modifier;
}
AlignmentAI::AlignmentAI()  {}
AlignmentAI::~AlignmentAI() {}

Vec2 AlignmentAI::compute(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed) {
	// Check if AI is enabled
	if (isEnabled()) {
		int numEntities = slotsUsed;
		if (numEntities == 1) {
			return Vec2::ZERO;
		}

		Vec2 avgVelocity = Vec2::ZERO;
		for (unsigned int i = 0; i < numEntities; i++) {
			// Calculate the average velocity of all nearby boids
			avgVelocity += nearbyEntities[i]->getVelocity();
		}

		m_DesiredVelocity = avgVelocity / (numEntities - 1);

		return applyReynoldsSteering(*entity, m_DesiredVelocity);
	}
	return Vec2::ZERO;
}