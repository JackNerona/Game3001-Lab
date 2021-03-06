#pragma once
#ifndef __STARSHIP__
#define __STARSHIP__

#include "Agent.h"

class StarShip final : public Agent 
{
public:
	StarShip();
	~StarShip();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	//getters and setters (accessors and mutators)
	float getMaxSpeed() const;
	float getTurnRate() const;
	float getAccelerationRate() const;
	glm::vec2 getDesiredVelocity() const;

	void setMaxSpeed(float speed);
	void setTurnRate(float angle);
	void setAccelerationRate(float rate);
	void setDesiredVelocity(glm::vec2 target_position);

	//public functions
	void Seek();
	void LookWhereYoureGoing(glm::vec2 target_direction);

private:
	//Private movement variables/properties
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	//where we want to go
	glm::vec2 m_desiredVelocity;

	//private functions
	void m_move();
};


#endif /* defined (__STARSHIP__) */