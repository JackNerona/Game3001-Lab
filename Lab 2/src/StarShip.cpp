#include "StarShip.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"


StarShip::StarShip()
{
	TextureManager::Instance().load("../Assets/textures/ncl.png", "Starship");

	const auto size = TextureManager::Instance().getTextureSize("Starship");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->acceleration = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	//Starting motion properties
	m_maxSpeed = 20.0f; // a maximum number of pixels moved per frame
	m_turnRate = 5.0f; // a maximum number of degrees to turn each step
	m_accelerationRate = 4.0f; // a maximum number of pixels to add to the velocity each frame

	setType(AGENT);
}

StarShip::~StarShip()
= default;

void StarShip::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the StarShip
	TextureManager::Instance().draw("Starship", x, y, 0, 255, true);
}

void StarShip::update()
{
	m_move();
}

void StarShip::clean()
{

}

float StarShip::getMaxSpeed() const
{
	return m_maxSpeed;
}
float StarShip::getTurnRate() const
{
	return m_turnRate;
}

float StarShip::getAccelerationRate() const
{
	return m_accelerationRate;
}

glm::vec2 StarShip::getDesiredVelocity() const
{
	return m_desiredVelocity;
}

void StarShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void StarShip::setTurnRate(const float angle)
{
	m_turnRate = angle;
}

void StarShip::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void StarShip::setDesiredVelocity(glm::vec2 target_position)
{
	m_desiredVelocity = Util::normalize(target_position - getTransform()->position);
}

void StarShip::Seek()
{
	setDesiredVelocity(getTargetPosition());

	// normalize the target direction (steering)
	const glm::vec2 steering_direction = getDesiredVelocity() - getCurrentDirection();

	setCurrentDirection(steering_direction); // instantly changing seek


	getRigidBody()->acceleration = getCurrentDirection() * getAccelerationRate();
}

void StarShip::LookWhereYoureGoing()
{

}

void StarShip::m_move()
{
	Seek();


	//								New Position   Position term   Velocity term	 Acceleration term
	//kenematic equation for motion --> Pf =           Pi      +   Vi*(time)     +    (0.5)*Ai*(time * time)

	const auto dt = TheGame::Instance().getDeltaTime();

	//Compute the position term
	const glm::vec2 initial_position = getTransform()->position;

	//compute the velocity term
	const auto velocity_term = getRigidBody()->velocity;// *dt;

	// Compute acceleration term
	const auto acceleration_term = getRigidBody()->acceleration * 0.5f;// *dt;



	//compute the new position
	glm::vec2 final_position = initial_position + velocity_term + acceleration_term;

	getTransform()->position = final_position;

	// add our acceleration to velocity
	getRigidBody()->velocity += getRigidBody()->acceleration;

	// clamp our velocity at max speed
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, getMaxSpeed());
}