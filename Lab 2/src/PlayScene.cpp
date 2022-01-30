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

	m_pTarget = new Target(); // Instantiating a new Target object - allocating memory on the heap
	//m_pTarget->getRigidBody()->velocity = glm::vec2(1.0f, 0.0f); Makes Target move continuously to the right
	addChild(m_pTarget);

	m_pStarShip = new StarShip();
	m_pStarShip->setCurrentHeading(0.0);
	m_pStarShip->getRigidBody()->velocity = m_pStarShip->getCurrentDirection() * m_pStarShip->getMaxSpeed();
	m_pStarShip->getRigidBody()->acceleration = m_pStarShip->getCurrentDirection() * m_pStarShip->getAccelerationRate();
	m_pStarShip->setEnabled(false);
	addChild(m_pStarShip);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Lab 2 Debug Properties", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Separator();

	// Target properties

	static float position[3] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target Position", position, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(position[0], position[1]);
	}
	
	ImGui::Separator();

	// Starship properties
	static bool toggleSeek = m_pStarShip->isEnabled();
	if (ImGui::Checkbox("Toggle Seek", &toggleSeek))
	{
		m_pStarShip->setEnabled(toggleSeek);
	}

	ImGui::End();
}
