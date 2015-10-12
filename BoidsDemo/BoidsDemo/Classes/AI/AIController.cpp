#include "AIController.h"
#include <iostream>

AIController::AIController() {}
AIController::~AIController() {
	for (int i = 0; i < behaviours.size(); i++) {
		delete behaviours[i];
	}
	for (int i = 0; i < externalForces.size(); i++) {
		delete externalForces[i];
	}
}

void AIController::applyAllForces(SpeciesEntity* const boid, const std::vector<SpeciesEntity*>& nearbyBoids, const int slotsUsed) {
	m_SteeringForce = Vec2::ZERO;
	// Apply AI behaviours
	for (unsigned int i = 0; i < behaviours.size(); i++) {
		m_SteeringForce += behaviours[i]->compute(boid, nearbyBoids, slotsUsed) * behaviours[i]->getModifier();
	}
	// Apply external forces
	for (unsigned int i = 0; i < externalForces.size(); i++) {
		m_SteeringForce += externalForces[i]->computeForceApplied(boid);
	}
	boid->setAcceleration(m_SteeringForce);
}