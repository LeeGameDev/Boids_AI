#include "Flock.h"
#include "Forces\Wind.h"

Flock::Flock(std::string xmlDocName) {
	// Data driven flock (XML)
	parseFlockXML(xmlDocName);
	parseAIControllerXML(m_AIControllerXMLDoc);
	parseSpeciesXML(m_SpeciesXMLDoc);

	m_AIController->setEnabled(false);
	populateFlock(m_Size);
	nearbyBoids.resize(m_Size);
	m_AIController->setEnabled(true);
}
Flock::~Flock() {
	delete m_AIController;
	delete m_Species;
}

void Flock::update(float dt) {
	if (!flip) {
		flip = true;
		return;
	}
	if (m_AIController->isEnabled()) {
		for (unsigned int i = 0; i < m_Size; i++) {
			// Prepare vector for populating
			slotsUsed = 0;

			// Check sqr distance from every other boid in the flock to populate nearbyBoids vector
			for (unsigned int j = 0; j < m_Size; j++) {
				b = boids[i];
				other = boids[j];
				bPos = b->getPosition();
				otherPos = other->getPosition();
				distance = bPos.distanceSquared(otherPos);

				// Other boid is close enough to check for visibility
				if ((distance > 0) && (distance < m_Species->m_DetectionRange)) {
					// Compute dot product of current boid heading, and other boid position relative to the current boid
					float dotResult = b->getVelocity().getNormalized().dot((bPos - otherPos).getNormalized());
					
					// If within threshold populate nearbyBoids
					if (dotResult > m_Species->m_DetectionDot) {
						nearbyBoids[slotsUsed] = other;
						++slotsUsed;
					}
				}
			}

			// Apply ai behaviours to the Boid
			m_AIController->applyAllForces(b, nearbyBoids, slotsUsed);
			b->update(dt);
			wrapEntity(*b);
		}
	}
}

void Flock::wrapEntity(SpeciesEntity& entity) const {
	Vec2 pos = entity.getPosition();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float spriteWidth = entity.getSprite()->getBoundingBox().size.width;

	if (pos.x < -spriteWidth) {
		pos.x = visibleSize.width + spriteWidth;
	}
	if (pos.x > visibleSize.width + spriteWidth) {
		pos.x = -spriteWidth;
	}
	if (pos.y < -spriteWidth) {
		pos.y = visibleSize.height + spriteWidth;
	}
	if (pos.y > visibleSize.height + spriteWidth) {
		pos.y = -spriteWidth;
	}
	entity.setPosition(pos);
}

void Flock::populateFlock(const int size) {
	// Instantiate flockSize number of Boids
	boids.resize(size);
	for (int i = 0; i < size; i++) {
		boids[i] = SpeciesEntity::create();
	}
}

void Flock::parseFlockXML(std::string xmlDocName) {
	unsigned char* buf = 0;
	try {
		std::string xmlDocPath = FileUtils::getInstance()->fullPathForFilename(xmlDocName);

		if (FileUtils::getInstance()->isFileExist(xmlDocName)) {
			ssize_t size;
			buf = FileUtils::getInstance()->getFileData(xmlDocPath, "r", &size);

			if (buf) {
				tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();

				if (tinyxml2::XML_NO_ERROR == xmlDoc->Parse((const char*)buf, size)) {
					tinyxml2::XMLElement* rootElement = xmlDoc->RootElement();

					if (rootElement) {
						tinyxml2::XMLElement* childElement = rootElement->FirstChildElement();

						while (childElement) {
							const char* elementName = childElement->Name();

							if (elementName) {
								if (strcmp(elementName, "name") == 0) {
									m_Name = childElement->GetText();
								}
								else if (strcmp(elementName, "size") == 0) {
									m_Size = atoi(childElement->GetText());
								}
								else if (strcmp(elementName, "speciesXML") == 0) {
									m_SpeciesXMLDoc = childElement->GetText();
								}
								else if (strcmp(elementName, "aiControllerXML") == 0) {
									m_AIControllerXMLDoc = childElement->GetText();
								}
							}
							childElement = childElement->NextSiblingElement();
						}
					}
				}
				delete xmlDoc;
			}
		}
	}
	catch (...) {

	}
}
void Flock::parseAIControllerXML(std::string xmlDocName) {
	unsigned char* buf = 0;
	try {
		std::string xmlDocPath = FileUtils::getInstance()->fullPathForFilename(xmlDocName);

		if (FileUtils::getInstance()->isFileExist(xmlDocName)) {
			ssize_t size;
			buf = FileUtils::getInstance()->getFileData(xmlDocPath, "r", &size);

			if (buf) {
				tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();

				if (tinyxml2::XML_NO_ERROR == xmlDoc->Parse((const char*)buf, size)) {
					tinyxml2::XMLElement* rootElement = xmlDoc->RootElement();

					if (rootElement) {
						tinyxml2::XMLElement* childElement = rootElement->FirstChildElement();
						m_AIController = new AIController();
						float alignmentModifier = 1.0f;
						bool alignmentEnabled = false;
						float cohesionModifier = 1.0f;
						bool cohesionEnabled = false;
						float separationModifier = 1.0f;
						bool separationEnabled = false;
						while (childElement) {
							const char* elementName = childElement->Name();

							if (elementName) {
								if (strcmp(elementName, "name") == 0) {
									m_AIController->setName(childElement->GetText());
								}
								else if (strcmp(elementName, "alignmentEnabled") == 0) {
									alignmentEnabled = strcmp(childElement->GetText(), "1") == 0;
								}
								else if (strcmp(elementName, "alignmentModifier") == 0) {
									alignmentModifier = atof(childElement->GetText());
								}
								else if (strcmp(elementName, "cohesionEnabled") == 0) {
									cohesionEnabled = strcmp(childElement->GetText(), "1") == 0;
								}
								else if (strcmp(elementName, "cohesionModifier") == 0) {
									cohesionModifier = atof(childElement->GetText());
								}
								else if (strcmp(elementName, "separationEnabled") == 0) {
									separationEnabled = strcmp(childElement->GetText(), "1") == 0;
								}
								else if (strcmp(elementName, "separationModifier") == 0) {
									separationModifier = atof(childElement->GetText());
								}
							}
							childElement = childElement->NextSiblingElement();
						}
						m_AIController->behaviours.push_back(new AlignmentAI(alignmentEnabled, alignmentModifier));
						m_AIController->behaviours.push_back(new CohesionAI(cohesionEnabled, cohesionModifier));
						m_AIController->behaviours.push_back(new SeparationAI(separationEnabled, separationModifier));
						m_AIController->externalForces.push_back(new Wind(Vec2(-0.05f, 0.03f)));
					}
				}
				delete xmlDoc;
			}
		}
	}
	catch (...) {

	}
}
void Flock::parseSpeciesXML(std::string xmlDocName) {
	unsigned char* buf = 0;
	try {
		std::string xmlDocPath = FileUtils::getInstance()->fullPathForFilename(xmlDocName);

		if (FileUtils::getInstance()->isFileExist(xmlDocName)) {
			ssize_t size;
			buf = FileUtils::getInstance()->getFileData(xmlDocPath, "r", &size);

			if (buf) {
				tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();

				if (tinyxml2::XML_NO_ERROR == xmlDoc->Parse((const char*)buf, size)) {
					tinyxml2::XMLElement* rootElement = xmlDoc->RootElement();

					if (rootElement) {
						tinyxml2::XMLElement* childElement = rootElement->FirstChildElement();
						const char* value;
						std::string name;
						std::string spriteFilename;
						float minSpeed;
						float maxSpeed;
						float maxAcceleration;
						float minSeparation;
						float detectionRange;
						float detectionDot;

						while (childElement) {
							const char* elementName = childElement->Name();

							if (elementName) {
								if (strcmp(elementName, "name") == 0) {
									name = childElement->GetText();
								}
								else if (strcmp(elementName, "spriteFilename") == 0) {
									spriteFilename = childElement->GetText();
								}
								else if (strcmp(elementName, "minSpeed") == 0) {
									minSpeed = atof(childElement->GetText());
								}
								else if (strcmp(elementName, "maxSpeed") == 0) {
									maxSpeed = atof(childElement->GetText());
								}
								else if (strcmp(elementName, "maxAcceleration") == 0) {
									maxAcceleration = atof(childElement->GetText());
								}
								else if (strcmp(elementName, "minSeparation") == 0) {
									minSeparation = atof(childElement->GetText());
								}
								else if (strcmp(elementName, "detectionRange") == 0) {
									detectionRange = atof(childElement->GetText());
								}
								else if (strcmp(elementName, "detectionDot") == 0) {
									detectionDot = atof(childElement->GetText());
								}
							}
							childElement = childElement->NextSiblingElement();
						}
						m_Species = new Species(name, spriteFilename, minSpeed, maxSpeed, maxAcceleration, minSeparation, detectionRange, detectionDot);
					}
				}
				delete xmlDoc;
			}
		}
	}
	catch (...) {

	}
}