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

	if (m_bDebugView)
	{
		Util::DrawCircle(m_pTarget->getTransform()->position, m_pTarget->getWidth() * 0.5f);

		if (m_pStarShip->isEnabled())
		{
			Util::DrawCircle(m_pStarShip->getTransform()->position, Util::max(m_pStarShip->getWidth() * 0.5f, m_pStarShip->getHeight() * 0.5f));
		}
	}
	
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	CollisionManager::squaredRadiusCheck(m_pStarShip, m_pTarget);
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

	m_pTarget = new Target(); // Instantiating a new Target object - allocating memory on the heap
	//m_pTarget->getRigidBody()->velocity = glm::vec2(1.0f, 0.0f); Makes Target move continuously to the right
	addChild(m_pTarget);

	m_pStarShip = new StarShip();
	m_pStarShip->setCurrentHeading(0.0);
	m_pStarShip->setTargetPosition(m_pTarget->getTransform()->position);
	m_pStarShip->getRigidBody()->acceleration = m_pStarShip->getCurrentDirection() * m_pStarShip->getAccelerationRate();
	m_pStarShip->setEnabled(false);
	addChild(m_pStarShip);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Lab 2 Debug Properties", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Separator();

	static bool toggleDebug = false;
	if (ImGui::Checkbox("Toggle Debug", &toggleDebug))
	{
		m_bDebugView = toggleDebug;
	}

	ImGui::Separator();

	// Target properties

	static float position[3] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target Position", position, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(position[0], position[1]);
		m_pStarShip->setTargetPosition(m_pTarget->getTransform()->position);
	}
	
	ImGui::Separator();

	// Starship properties
	static bool toggleSeek = m_pStarShip->isEnabled();
	if (ImGui::Checkbox("Toggle Seek", &toggleSeek))
	{
		m_pStarShip->setEnabled(toggleSeek);
	}

	static float speed = m_pStarShip->getMaxSpeed();
	if (ImGui::SliderFloat("Max Speed", &speed, 0.0f, 100.0f))
	{
		m_pStarShip->setMaxSpeed(speed);
	}

	static float acceleration = m_pStarShip->getAccelerationRate();
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration, 0.0f, 500.0f))
	{
		m_pStarShip->setAccelerationRate(acceleration);
		m_pStarShip->getRigidBody()->acceleration = m_pStarShip->getCurrentDirection() * m_pStarShip->getAccelerationRate();
	}

	static float turn_rate = m_pStarShip->getTurnRate();
	if (ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pStarShip->setTurnRate(turn_rate);
	}

	if (ImGui::Button("Reset"))
	{
		// reset ship's postition
		m_pStarShip->getTransform()->position = glm::vec2(100.0f, 400.0f);
		
		// reset target's position
		m_pTarget->getTransform()->position = glm::vec2(500.0f, 100.0f);
		
		// reset current headin (orientation), velocity and acceleration
		m_pStarShip->setCurrentHeading(0.0);
		m_pStarShip->getRigidBody()->velocity = glm::vec2(0.0);
		m_pStarShip->getRigidBody()->acceleration = m_pStarShip->getCurrentDirection() * m_pStarShip->getAccelerationRate();

		m_pStarShip->setTargetPosition(m_pTarget->getTransform()->position);

	}

	ImGui::End();
}
