/*! \file Force.h */

#ifndef __FORCE_H__
#define __FORCE_H__

#include "cocos2d.h"
#include "SpeciesEntity.h"

USING_NS_CC;

/*! \class Force

	\brief Controls a SpeciesEntity externally.

	Base class for a Force that controls a SpeciesEntity externally.
*/
class Force
{
public:
	Force();
	virtual ~Force();

	/*! \brief Computes the Force applied by the wind on the SpeciesEntity.

		\param entity The SpeciesEntity with which to apply the force.

		\return The steering force of the wind.
	*/
	virtual Vec2 computeForceApplied(SpeciesEntity* entity) = 0;
};

#endif __FORCE_H__