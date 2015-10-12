/*! \file SpeciesEntity.cpp */

#include "SpeciesEntity.h"
#include <random>

#define randVec2(MIN_X, MAX_X, MIN_Y, MAX_Y) Vec2(MIN_X + (rand() / (RAND_MAX / MAX_X)), MIN_Y + (rand() / (RAND_MAX / MAX_Y)))

bool SpeciesEntity::initWithSpecies(const Species& type) {
	m_Species = &type;
	m_Sprite = Sprite::create(m_Species->m_SpriteFilename);

	if (m_Sprite) {
		m_Sprite->setScale(0.5f, 0.5f);
	}
	float maxValue = m_Species->m_MaxSpeed;
	float maxForce = m_Species->m_MaxAcceleration;
	m_Velocity = Vec2(random(-maxValue, maxValue), random(-maxValue, maxValue));
	m_Acceleration = Vec2(random(-maxForce, maxForce), random(-maxForce, maxForce));
	addChild(m_Sprite); // !!!

	return true;
}

void SpeciesEntity::update(float dt) {
	// Update velocity and clamp to max value
	m_Velocity += m_Acceleration;
	Vec2 direction = m_Velocity.getNormalized();
	if (m_Velocity.length() > m_Species->m_MaxSpeed) {
		m_Velocity = direction * m_Species->m_MaxSpeed;
	}
	else if (m_Velocity.length() < m_Species->m_MinSpeed) {
		m_Velocity = direction * m_Species->m_MinSpeed;
	}
	
	// Update position
	setPosition(getPosition() + m_Velocity);

	// Update rotation
	setRotation(getHeading());
}