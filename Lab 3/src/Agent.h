#pragma once
#ifndef __AGENT__
#define __AGENT__

#include <glm/vec4.hpp>
#include "DisplayObject.h"

class Agent : public DisplayObject
{
public:
	Agent();
	~Agent();

	// Inherited via GameObject
	void draw() override = 0;
	void update() override = 0;
	void clean() override = 0;

	// getters (accessors)
	glm::vec2 getTargetPosition() const;
	glm::vec2 getCurrentDirection() const;
	float getLOSDistance() const;
	bool hasLOS() const;
	float getCurrentHeading() const;
	glm::vec4 getLOSColour() const;

	glm::vec2 getLeftLOSEndPoint() const;
	glm::vec2 getMiddleLOSEndPoint() const;
	glm::vec2 getRightLOSEndPoint() const;
	glm::vec2 getfarLeftLOSEndPoint() const;
	glm::vec2 getfarRightLOSEndPoint() const;
	bool* getCollisionWhiskers(); // returns entire array
	glm::vec4 getLineColour(int index);
	float getWhiskerAngle() const;


	// setters (Mutators)
	void setTargetPosition(glm::vec2 new_position);
	void setCurrentDirection(glm::vec2 new_direction);
	void setLOSDistance(float distance);
	void setHasLOS(bool state);
	void setCurrentHeading(float heading);
	void setLOSColour(glm::vec4 colour);

	void setLeftLOSEndPoint(glm::vec2 point);
	void setMiddleLOSEndPoint(glm::vec2 point);
	void setRightLOSEndPoint(glm::vec2 point);
	void setfarLeftLOSEndPoint(glm::vec2 point);
	void setfarRightLOSEndPoint(glm::vec2 point);
	void setLineColour(int index, glm::vec4 colour);
	void seWhiskerAngle(float angle);

	// public functions
	void updateWhiskers(float angle);

private:
	void m_changeDirection();
	float m_currentHeading; // angle the ship is looking
	glm::vec2 m_currentDirection; // vector the ship is moving
	glm::vec2 m_targetPosition; // vector representing the target.position

	// LOS
	float m_LOSDistance;
	bool m_hasLOS;
	glm::vec4 m_LOSColour;

	//Whiskers
	glm::vec2 m_leftLOSEndPoint;
	glm::vec2 m_middleLOSEndPoint;
	glm::vec2 m_rightLOSEndPoint;
	glm::vec2 m_farLeftLOSEndPoint;
	glm::vec2 m_farRightLOSEndPoint;
	glm::vec4 m_lineColour[5]; // you will need to change this to 5
	bool m_collisionWhiskers[5]; // Change to 5 - keeps track of each whisker collision

	float m_whiskerAngle; // angle of left and right whiskers relative to heading
};



#endif /* defined ( __AGENT__) */