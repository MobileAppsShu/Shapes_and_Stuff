#include "gameoverMenu.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "game.h"
#include "scene.h"
#include "mainMenu.h"
#include "audio.h"

GameOverMenu::~GameOverMenu()
{}

void GameOverMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect Screen Tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();

		if (conPlay->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to game scene
			Game* game = (Game*)g_pSceneManager->Find("game");
			g_pSceneManager->SwitchTo(game);
			game->Yplaying();

			// Resume game
			//game->resetGame();

			// Restore button alpha state
			GameOverMenu* menu = (GameOverMenu*)g_pSceneManager->Find("gameovermenu");
			menu->getConGameButton()->m_Alpha = 1.0f;
		}
		else if (menuButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Switch to menu scene
			MainMenu* menu = (MainMenu*)g_pSceneManager->Find("mainmenu");
			g_pSceneManager->SwitchTo(menu);

			// Start menu music
			Audio::PlayMusic("audio/GTOET_10_Gawp.mp3");
		}
	}
}

void GameOverMenu::Render()
{
	Scene::Render();
}

void GameOverMenu::Init()
{
	Scene::Init();
	Game* game = (Game*)g_pSceneManager->Find("game");

	// Create Game Over logo
	float y_posGameoverImage = (float)IwGxGetScreenHeight() * 0.2f;
	gameoverImage = new CSprite();
	gameoverImage->SetImage(g_pResources->getGameoverImage());
	gameoverImage->m_X = IwGxGetScreenWidth() / 2;
	gameoverImage->m_Y = y_posGameoverImage;
	gameoverImage->m_W = gameoverImage->GetImage()->GetWidth();
	gameoverImage->m_H = gameoverImage->GetImage()->GetHeight();
	gameoverImage->m_AnchorX = 0.5f;
	gameoverImage->m_AnchorY = 0.5f;
	gameoverImage->m_ScaleX = 0.75f;
	gameoverImage->m_ScaleY = 0.75f;
	AddChild(gameoverImage);

	// Create Continue Game button
	float y_posContinue = (float)IwGxGetScreenHeight() * 0.80f;
	conPlay = new CSprite();
	conPlay->SetImage(g_pResources->getConPlay());
	conPlay->m_X = IwGxGetScreenWidth() / 2;
	conPlay->m_Y = y_posContinue;
	conPlay->m_W = conPlay->GetImage()->GetWidth();
	conPlay->m_H = conPlay->GetImage()->GetHeight();
	conPlay->m_AnchorX = 0.5f;
	conPlay->m_AnchorY = 0.5f;
	conPlay->m_ScaleX = 1.0f;
	conPlay->m_ScaleY = 1.0f;
	AddChild(conPlay);

	// Create Menu button
	float y_posRTM = (float)IwGxGetScreenHeight() * 0.93f;
	menuButton = new CSprite();
	menuButton->SetImage(g_pResources->getMenuButton());
	menuButton->m_X = IwGxGetScreenWidth() / 2;
	menuButton->m_Y = y_posRTM;
	menuButton->m_W = menuButton->GetImage()->GetWidth();
	menuButton->m_H = menuButton->GetImage()->GetHeight();
	menuButton->m_AnchorX = 0.5f;
	menuButton->m_AnchorY = 0.5f;
	menuButton->m_ScaleX = 1.0f;
	menuButton->m_ScaleY = 1.0f;
	AddChild(menuButton);

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