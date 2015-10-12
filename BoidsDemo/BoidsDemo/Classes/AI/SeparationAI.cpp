#include "SeparationAI.h"

SeparationAI::SeparationAI(bool isEnabled, float modifier) {
	m_IsEnabled = isEnabled;
	m_Modifier = modifier;
}
SeparationAI::SeparationAI()  {}
SeparationAI::~SeparationAI() {}

Vec2 SeparationAI::compute(SpeciesEntity* const entity, const std::vector<SpeciesEntity*>& nearbyEntities, const int slotsUsed) {
	// Check if AI is enabled
	if (isEnabled()) {
		int numBoids = slotsUsed;
		if (numBoids == 1) {
			return Vec2::ZERO;
		}

		Vec2 avgDelta = Vec2::ZERO;
		for (unsigned int i = 0; i < numBoids; i++) {
			if (entity != nearbyEntities[i]) {
				// Check if any nearbyBoids are too close
				float distanceSquared = entity->getPosition().distanceSquared(nearbyEntities[i]->getPosition());
				if (distanceSquared < entity->getSpecies()->m_MinSeparation) {
					Vec2 delta = entity->getPosition() - nearbyEntities[i]->getPosition();
					delta.normalize();
					// Apply distance weighting
					delta = delta / distanceSquared;
					avgDelta += delta;
				}
			}
		}

		m_DesiredVelocity = avgDelta / (numBoids - 1);

		return applyReynoldsSteering(*entity, m_DesiredVelocity);
	}
	return Vec2::ZERO;
}