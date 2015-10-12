/*! \file Species.h */

#ifndef __SPECIES_H__
#define __SPECIES_H__

#include "cocos2d.h"

USING_NS_CC;

/*! \class Species

	\brief Data pertaining to an entity used in a flocking algorithm.

	Species type contains data pertaining to an entity used in a flocking algorithm.
*/
class Species
{
public:
	const std::string	m_Name				= "";				///< Species name
	const std::string	m_SpriteFilename	= "default.png";	///< Sprite filename [no path]
	const float			m_MinSpeed			= 1.0f;				///< Minimum speed at which the Species moves
	const float			m_MaxSpeed			= 2.0f;				///< Maximum speed at which the Species moves
	const float			m_MaxAcceleration	= 0.03f;			///< Maximum value at which the Species accelerates
	const float			m_MinSeparation		= 500.0f;			///< Desired separation distance squared (OpenGL units)
	const float			m_DetectionRange	= 2500.0f;			///< Detection range squared for other SpeciesEntity (OpenGL units)
	const float			m_DetectionDot		= -0.75f;			///< Detection angle for other SpeciesEntity (value from -1 to 1, represented as the result of a dot product)

	/*! \brief Constructor for a fully specified Species object */
	Species(const std::string& name, const std::string& spriteFilename, float minSpeed, float maxSpeed, float maxAcceleration, float minSeparation, float detectionRange, float detectionDot) :
		m_Name(name),
		m_SpriteFilename(spriteFilename),
		m_MinSpeed(minSpeed),
		m_MaxSpeed(maxSpeed),
		m_MaxAcceleration(maxAcceleration),
		m_MinSeparation(minSeparation),
		m_DetectionRange(detectionRange),
		m_DetectionDot(detectionDot) {

		// Create the graphical display for the Species as a Sprite
		m_Sprite = Sprite::create(m_SpriteFilename);
	}

	Species() {
		// Create the graphical display for the Species as a Sprite
		m_Sprite = Sprite::create(m_SpriteFilename);
	}

	virtual ~Species() {}

	/*! \brief Gets the Sprite created by the constructor Species constructor.

		\return A pointer to the Sprite.
	*/
	inline Sprite* getSprite() const { return m_Sprite; }

private:
	Sprite* m_Sprite;	// The Sprite is the graphical display of the Species.
};

#endif __SPECIES_H__