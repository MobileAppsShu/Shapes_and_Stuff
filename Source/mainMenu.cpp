#include "mainMenu.h"
#include "about.h"
#include "settings.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "audio.h"
#include "game.h"

MainMenu::~MainMenu()
{
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		if (aboutButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to About Menu scene
			About* about = (About*)g_pSceneManager->Find("aboutmenu");
			g_pSceneManager->SwitchTo(about);
		}
		else if (settingsButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to Settings Menu scene
			Settings* settings = (Settings*)g_pSceneManager->Find("settingsmenu");
			g_pSceneManager->SwitchTo(settings);
		}
		else if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to game scene
			Game* game = (Game*)g_pSceneManager->Find("game");
			g_pSceneManager->SwitchTo(game);

			// Create new game
			game->resetGame();
			game->Yplaying();

			// Start game music
			Audio::PlayMusic("audio/GTOET_03_Beach.mp3", true);
		}
	}
}

void MainMenu::Render()
{
	Scene::Render();
}

void MainMenu::initBackUI() // Height = 750 | Width = 1334
{
	// Create Shapes - Squares
	float x_posShapesSquare = 40.0f + ((float)IwGxGetScreenWidth() / 7);
	float y_posShapesSquare = (float)IwGxGetScreenHeight() * 0.41f;
	ShapesSquare = new CSprite();
	ShapesSquare->SetImage(g_pResources->getGameSquare());
	ShapesSquare->m_X = x_posShapesSquare;
	ShapesSquare->m_Y = y_posShapesSquare;
	ShapesSquare->m_W = ShapesSquare->GetImage()->GetWidth();
	ShapesSquare->m_H = ShapesSquare->GetImage()->GetHeight();
	ShapesSquare->m_AnchorX = 0.0f;
	ShapesSquare->m_AnchorY = 0.0f;
	ShapesSquare->m_ScaleX = 0.5f;
	ShapesSquare->m_ScaleY = 0.5f;
	AddChild(ShapesSquare);

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

	// Create Shapes - Star
	float x_posShapesStar = 40.0f + (((float)IwGxGetScreenWidth() * 3 / 7));
	float y_posShapesStar = (float)IwGxGetScreenHeight() * 0.41f;
	ShapesStar = new CSprite();
	ShapesStar->SetImage(g_pResources->getGameBowieStar());
	ShapesStar->m_X = x_posShapesStar;
	ShapesStar->m_Y = y_posShapesStar;
	ShapesStar->m_W = ShapesStar->GetImage()->GetWidth();
	ShapesStar->m_H = ShapesStar->GetImage()->GetHeight();
	ShapesStar->m_AnchorX = 0.0f;
	ShapesStar->m_AnchorY = 0.0f;
	ShapesStar->m_ScaleX = 0.5f;
	ShapesStar->m_ScaleY = 0.5f;
	AddChild(ShapesStar);

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

	// Create Shapes - Circle
	float x_posShapesCircle = 40.0f + (((float)IwGxGetScreenWidth() * 5 / 7));
	float y_posShapesCircle = (float)IwGxGetScreenHeight() * 0.41f;
	ShapesCircle = new CSprite();
	ShapesCircle->SetImage(g_pResources->getGameCircle());
	ShapesCircle->m_X = x_posShapesCircle;
	ShapesCircle->m_Y = y_posShapesCircle;
	ShapesCircle->m_W = ShapesCircle->GetImage()->GetWidth();
	ShapesCircle->m_H = ShapesCircle->GetImage()->GetHeight();
	ShapesCircle->m_AnchorX = 0.0f;
	ShapesCircle->m_AnchorY = 0.0f;
	ShapesCircle->m_ScaleX = 0.5f;
	ShapesCircle->m_ScaleY = 0.5f;
	AddChild(ShapesCircle);
}

void MainMenu::Init()
{
	Scene::Init();

	Game* game = (Game*)g_pSceneManager->Find("game");
	//About* about = (About*)g_pSceneManager->Find("aboutmenu");

	// Create Logo
	float y_posLogo = (float)IwGxGetScreenHeight() * 0.2f;
	logo = new CSprite();
	logo->SetImage(g_pResources->getLogo());
	logo->m_X = IwGxGetScreenWidth() / 2.0f;
	logo->m_Y = y_posLogo;
	logo->m_W = logo->GetImage()->GetWidth();
	logo->m_H = logo->GetImage()->GetHeight();
	logo->m_AnchorX = 0.5f;
	logo->m_AnchorY = 0.5f;
	logo->m_ScaleX = 1.0f;
	logo->m_ScaleY = 1.0f;
	AddChild(logo);

	// Create Play button
	float y_posPlay = (float)IwGxGetScreenHeight() * 0.67f;
	playButton = new CSprite();
	playButton->SetImage(g_pResources->getPlayButton());
	playButton->m_X = IwGxGetScreenWidth() / 2.0f;
	playButton->m_Y = y_posPlay;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 0.5f;
	playButton->m_AnchorY = 0.5f;
	playButton->m_ScaleX = 1.0f;
	playButton->m_ScaleY = 1.0f;
	AddChild(playButton);

	// Create About button
	float y_posAbout = (float)IwGxGetScreenHeight() * 0.80f;
	aboutButton = new CSprite();
	aboutButton->SetImage(g_pResources->getAboutButton());
	aboutButton->m_X = IwGxGetScreenWidth() / 2.0f;
	aboutButton->m_Y = y_posAbout;
	aboutButton->m_W = aboutButton->GetImage()->GetWidth();
	aboutButton->m_H = aboutButton->GetImage()->GetHeight();
	aboutButton->m_AnchorX = 0.5f;
	aboutButton->m_AnchorY = 0.5f;
	aboutButton->m_ScaleX = 1.0f;
	aboutButton->m_ScaleY = 1.0f;
	AddChild(aboutButton);

	// Create Settings button
	float y_posSettings = (float)IwGxGetScreenHeight() * 0.93f;
	settingsButton = new CSprite();
	settingsButton->SetImage(g_pResources->getSettingsButton());
	settingsButton->m_X = IwGxGetScreenWidth() / 2.0f;
	settingsButton->m_Y = y_posSettings;
	settingsButton->m_W = settingsButton->GetImage()->GetWidth();
	settingsButton->m_H = settingsButton->GetImage()->GetHeight();
	settingsButton->m_AnchorX = 0.5f;
	settingsButton->m_AnchorY = 0.5f;
	settingsButton->m_ScaleX = 1.0f;
	settingsButton->m_ScaleY = 1.0f;
	AddChild(settingsButton);

	// Initialise UI
	initBackUI();

	// Start menu music
	Audio::PlayMusic("audio/GTOET_10_Gawp.mp3");
}