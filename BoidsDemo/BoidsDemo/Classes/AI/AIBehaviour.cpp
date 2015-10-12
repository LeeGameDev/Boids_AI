#include "AIBehaviour.h"

AIBehaviour::AIBehaviour() {}
AIBehaviour::~AIBehaviour() {}

Vec2 AIBehaviour::applyReynoldsSteering(const SpeciesEntity& entity, Vec2 desiredVelocity) const {
	const Species* entitySpecies = entity.getSpecies();
	desiredVelocity.normalize();
	desiredVelocity *= entitySpecies->m_MaxSpeed;

	Vec2 steeringForce = desiredVelocity - entity.getVelocity();
	Vec2 maxForce = Vec2::ONE * entitySpecies->m_MaxAcceleration;
	steeringForce.clamp(-maxForce, maxForce);

	return steeringForce;
}