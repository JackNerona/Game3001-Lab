#include "StarShip.h"
#include "TextureManager.h"


StarShip::StarShip()
{
	TextureManager::Instance().load("../Assets/textures/ncl.png", "Starship");

	const auto size = TextureManager::Instance().getTextureSize("Starship");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(600.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(SPACE_SHIP);
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

}

void StarShip::clean()
{
}