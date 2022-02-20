#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_bDebugView = false;

	m_pTarget = new Target(); // instantiating a new Target object - allocating memory on the Heap
	addChild(m_pTarget);

	m_pSpaceShip = new SpaceShip();
	addChild(m_pSpaceShip);

	//m_pObstacle = new Obstacle();
	//addChild(m_pObstacle);

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/thunder.ogg", "boom", SOUND_SFX);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Lab 4 Debug Properties", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Separator();

	/*static bool toggleSeek = m_pSpaceShip->isEnabled();
	if (ImGui::Checkbox("Toggle Seek", &toggleSeek))
	{
		m_pSpaceShip->setEnabled(toggleSeek);
	}*/

	static bool toggleDebug = false;
	if (ImGui::Checkbox("Toggle Debug", &toggleDebug))
	{
		m_bDebugView = toggleDebug;
	}
	
	ImGui::Separator();

	// spaceship properties

	static float start_position[2] = { m_pSpaceShip->getTransform()->position.x, m_pSpaceShip->getTransform()->position.y };
	if (ImGui::SliderFloat2("Start Position", start_position, 0.0f, 800.0f))
	{
		m_pSpaceShip->getTransform()->position = glm::vec2(start_position[0], start_position[1]);
	}

	// target properties
	
	static float goal_position[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Goal Position", goal_position, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(goal_position[0], goal_position[1]);
	}

	ImGui::End();
}

//void PlayScene::doWhiskerCollision()
//{
//	SDL_Rect box = { (int)m_pObstacle->getTransform()->position.x - m_pObstacle->getWidth() * 0.5f,
//		(int)m_pObstacle->getTransform()->position.y - m_pObstacle->getHeight() * 0.5f,
//		(int)m_pObstacle->getWidth(), (int)m_pObstacle->getHeight() };
//
//	SDL_Point ship_origin = { (int)m_pSpaceShip->getTransform()->position.x, (int)m_pSpaceShip->getTransform()->position.y };
//	// End points for whiskers:
//	SDL_Point left = { (int)m_pSpaceShip->getLeftLOSEndPoint().x, (int)m_pSpaceShip->getLeftLOSEndPoint().y };
//	SDL_Point middle = { (int)m_pSpaceShip->getMiddleLOSEndPoint().x, (int)m_pSpaceShip->getMiddleLOSEndPoint().y };
//	SDL_Point right = { (int)m_pSpaceShip->getRightLOSEndPoint().x, (int)m_pSpaceShip->getRightLOSEndPoint().y };
//
//	bool collisions[3] = { 0,0,0 }; // Refactoring: use getCollisionWhiskers from SpaceShip.
//
//	SDL_Point ship = ship_origin; // Something really annoying in the SDL method is that the lines get clipped, so we need to reset the lines.
//	collisions[0] = SDL_IntersectRectAndLine(&box, &ship.x, &ship.y, &left.x, &left.y);
//	ship = ship_origin;
//	collisions[1] = SDL_IntersectRectAndLine(&box, &ship.x, &ship.y, &middle.x, &middle.y);
//	ship = ship_origin;
//	collisions[2] = SDL_IntersectRectAndLine(&box, &ship.x, &ship.y, &right.x, &right.y);
//
//	for (unsigned int i = 0; i < 3; i++)
//	{
//		m_pSpaceShip->getCollisionWhiskers()[i] = collisions[i];
//		m_pSpaceShip->setLineColor(i, (collisions[i] ? glm::vec4(1, 0, 0, 1) : glm::vec4(0, 1, 0, 1)));
//	}
//}
