#include "Wind.h"

Wind::Wind(Vec2 velocity) : m_Velocity(velocity) {}
Wind::Wind()  {}
Wind::~Wind() {}

Vec2 Wind::computeForceApplied(SpeciesEntity* entity) {
	return m_Velocity;
}