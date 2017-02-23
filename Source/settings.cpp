#include "settings.h"
#include "mainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "audio.h"

Settings::~Settings()
{
}

void Settings::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		if (menuButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to menu scene
			MainMenu* menu = (MainMenu*)g_pSceneManager->Find("mainmenu");
			g_pSceneManager->SwitchTo(menu);
		}
		else if (muteButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Mute game music
			Audio::StopMusic();
		}
	}
}

void Settings::Render()
{
	Scene::Render();
}

void Settings::Init()
{
	Scene::Init();

	//Game* game = (Game*)g_pSceneManager->Find("game");
	//MainMenu* menu = (MainMenu*)g_pSceneManager->Find("mainmenu");

	// Create Setting Image
	float y_posSettingImg = (float)IwGxGetScreenHeight() * 0.1f;
	settingImage = new CSprite();
	settingImage->SetImage(g_pResources->getSettingImage());
	settingImage->m_X = IwGxGetScreenWidth() / 2.0f;
	settingImage->m_Y = y_posSettingImg;
	settingImage->m_W = settingImage->GetImage()->GetWidth();
	settingImage->m_H = settingImage->GetImage()->GetHeight();
	settingImage->m_AnchorX = 0.5f;
	settingImage->m_AnchorY = 0.5f;
	settingImage->m_ScaleX = 0.75f;
	settingImage->m_ScaleY = 0.75f;
	AddChild(settingImage);

	// Create Menu button
	float y_posMenu = (float)IwGxGetScreenHeight() * 0.93f;
	menuButton = new CSprite();
	menuButton->SetImage(g_pResources->getMenuButton());
	menuButton->m_X = IwGxGetScreenWidth() / 2.0f;
	menuButton->m_Y = y_posMenu;
	menuButton->m_W = menuButton->GetImage()->GetWidth();
	menuButton->m_H = menuButton->GetImage()->GetHeight();
	menuButton->m_AnchorX = 0.5f;
	menuButton->m_AnchorY = 0.5f;
	menuButton->m_ScaleX = 1.0f;
	menuButton->m_ScaleY = 1.0f;
	AddChild(menuButton);

	// Create Shapes - Triangle
	float x_posShapesTriangle = 40.0f + (((float)IwGxGetScreenWidth() * 2 / 7));
	float y_posShapesTriangle = (float)IwGxGetScreenHeight() * 0.41f;
	ShapesTriangle = new CSprite();
	ShapesTriangle->SetImage(g_pResources->getGameTriangle());
	ShapesTriangle->m_X = x_posShapesTriangle;
	ShapesTriangle->m_Y = y_posShapesTriangle;
	ShapesTriangle->m_W = ShapesTriangle->GetImage()->GetWidth();
	ShapesTriangle->m_H = ShapesTriangle->GetImage()->GetHeight();
	ShapesTriangle->m_AnchorX = 0.0f;
	ShapesTriangle->m_AnchorY = 0.0f;
	ShapesTriangle->m_ScaleX = 0.5f;
	ShapesTriangle->m_ScaleY = 0.5f;
	AddChild(ShapesTriangle);

	// Create Mute Button
	float x_posmuteButton = IwGxGetScreenWidth() / 2.0f;
	float y_posmuteButton = (float)IwGxGetScreenHeight() * 0.5f;
	muteButton = new CSprite();
	muteButton->SetImage(g_pResources->getMuteButton());
	muteButton->m_X = x_posmuteButton;
	muteButton->m_Y = y_posmuteButton;
	muteButton->m_W = muteButton->GetImage()->GetWidth();
	muteButton->m_H = muteButton->GetImage()->GetHeight();
	muteButton->m_AnchorX = 0.5f;
	muteButton->m_AnchorY = 0.5f;
	muteButton->m_ScaleX = 0.5f;
	muteButton->m_ScaleY = 0.5f;
	AddChild(muteButton);

	// Create Shapes - Hexagon
	float x_posShapesHexagon = 40.0f + (((float)IwGxGetScreenWidth() * 4 / 7));
	float y_posShapesHexagon = (float)IwGxGetScreenHeight() * 0.41f;
	ShapesHexagon = new CSprite();
	ShapesHexagon->SetImage(g_pResources->getGameHexagon());
	ShapesHexagon->m_X = x_posShapesHexagon;
	ShapesHexagon->m_Y = y_posShapesHexagon;
	ShapesHexagon->m_W = ShapesHexagon->GetImage()->GetWidth();
	ShapesHexagon->m_H = ShapesHexagon->GetImage()->GetHeight();
	ShapesHexagon->m_AnchorX = 0.0f;
	ShapesHexagon->m_AnchorY = 0.0f;
	ShapesHexagon->m_ScaleX = 0.5f;
	ShapesHexagon->m_ScaleY = 0.5f;
	AddChild(ShapesHexagon);
}