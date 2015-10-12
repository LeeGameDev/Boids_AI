/*! \file Flock.h */

#ifndef __FLOCK_H__
#define __FLOCK_H__

#include <vector>
#include <stdlib.h>

#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"
#include "AI\AIController.h"
#include "AI\AlignmentAI.h"
#include "AI\CohesionAI.h"
#include "AI\SeparationAI.h"
#include "Species.h"
#include "SpeciesEntity.h"
#include <vld.h>

/*! \see SpeciesEntity */
class SpeciesEntity;

/*! \see AIController */
class AIController;

USING_NS_CC;

/*! \class Flock

	\brief Representation of all SpeciesEntity.

	Holds the SpeciesEntity in its entirety and has an AIController that directs the \
	movement of the Flock as a whole.
*/
class Flock
{
public:
	std::vector<SpeciesEntity*> boids;			///< Container for all SpeciesEntity
	std::vector<SpeciesEntity*> nearbyBoids;	///< Container to cache all nearby SpeciesEntity for AI Computation

	/*! \brief Constructor for a Flock that parses the XML document for its data.

		\see parseFlockXML(std::string)
		\see populateFlock(int)

		\param xmlDocName The XML Document filename.
	*/
	Flock(std::string xmlDocName);

	/*! \brief Destructor for a Flock that cleans up the Species and AIController pointers. */
	virtual ~Flock();

	/*! \brief Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".

		\param dt In seconds.
	*/
	void update(float dt);

	/*! \brief Gets the size of the flock.

		\return The flock size.
	*/
	inline int getSize() const { return m_Size; }

	/*! \brief Gets the AIController that controls the movement of the Flock.
	
		\see parseAIControllerXML(string)

		\return A pointer to the AIController.
	*/
	inline AIController* getAIController() const { return m_AIController; }

	/*! \brief Gets the Species type that defines the SpeciesEntity in this Flock.
	
		\see parseSpeciesXML(std::string)

		\return A pointer to the Species type.
	*/
	inline const Species* getSpecies() const { return m_Species; }
private:
	std::string	m_Name = "Boids Flock";		// Flock name
	unsigned int m_Size = 150;				// Flock size
	std::string	m_SpeciesXMLDoc = "";		// Species data XML Document filename
	std::string	m_AIControllerXMLDoc = "";	// AIController data XML Document filename
	AIController* m_AIController;			// Pointer to the AIController
	const Species*	m_Species;				// Pointer to the Species data

	// Cached values for computation
	SpeciesEntity* b;
	SpeciesEntity* other;
	Vec2 bPos;
	Vec2 otherPos;
	float distance;
	float slotsUsed;
	bool flip = false;

	// Keeps a SpeciesEntity on the screen by wrapping its position if it goes off screen.
	void wrapEntity(SpeciesEntity& entity) const;

	// Instantiates size amount of SpeciesEntity into the Flock.
	void populateFlock(const int size);

	// Parses an XML Document for Flock data.
	void parseFlockXML(std::string xmlDocName);

	// Parses an XML Document for Species data.
	void parseSpeciesXML(std::string xmlDocName);

	// Parses an XML Document for AIController data.
	void parseAIControllerXML(std::string xmlDocName);
};

#endif __FLOCK_H__