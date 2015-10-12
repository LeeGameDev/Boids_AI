#include "CohesionAI.h"

CohesionAI::CohesionAI(bool isEnabled, float modifier) {
	m_IsEnabled = isEnabled;
	m_Modifier = modifier;
}
CohesionAI::CohesionAI()  {}
CohesionAI::~CohesionAI() {}

Vec2 CohesionAI::compute(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed) {
	// Check if AI is enabled
	if (isEnabled()) {
		int numEntities = slotsUsed;
		if (numEntities == 1) {
			return Vec2::ZERO;
		}

		Vec2 avgPos = Vec2::ZERO;
		for (unsigned int i = 0; i < numEntities; i++) {
			if (entity != nearbyEntities[i]) {
				// Calculate the average position of all nearbyBoids
				avgPos += nearbyEntities[i]->getPosition();
			}
		}

		avgPos = avgPos / (numEntities - 1);

		m_DesiredVelocity = (avgPos - entity->getPosition());
		return applyReynoldsSteering(*entity, m_DesiredVelocity);
	}
	return Vec2::ZERO;
}