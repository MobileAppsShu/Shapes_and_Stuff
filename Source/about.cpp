#include "about.h"
#include "mainMenu.h"
#include "settings.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "audio.h"

About::~About()
{
}

void About::Update(float deltaTime, float alphaMul)
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
	}
}

void About::Render()
{
	Scene::Render();
}

void About::Init()
{
	Scene::Init();

	//Game* game = (Game*)g_pSceneManager->Find("game");
	//MainMenu* menu = (MainMenu*)g_pSceneManager->Find("mainmenu");

	// Create About Image
	float y_posAboutImg = (float)IwGxGetScreenHeight() * 0.1f;
	aboutImage = new CSprite();
	aboutImage->SetImage(g_pResources->getAboutImage());
	aboutImage->m_X = IwGxGetScreenWidth() / 2.0f;
	aboutImage->m_Y = y_posAboutImg;
	aboutImage->m_W = aboutImage->GetImage()->GetWidth();
	aboutImage->m_H = aboutImage->GetImage()->GetHeight();
	aboutImage->m_AnchorX = 0.5f;
	aboutImage->m_AnchorY = 0.5f;
	aboutImage->m_ScaleX = 0.75f;
	aboutImage->m_ScaleY = 0.75f;
	AddChild(aboutImage);

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

	// On-Screen - Developer
	float y_posOSDev = (float)IwGxGetScreenHeight() * 0.25f;
	OSDev = new CSprite();
	OSDev->SetImage(g_pResources->getAbout_Developers());
	OSDev->m_X = IwGxGetScreenWidth() / 2.0f;
	OSDev->m_Y = y_posOSDev;
	OSDev->m_W = OSDev->GetImage()->GetWidth();
	OSDev->m_H = OSDev->GetImage()->GetHeight();
	OSDev->m_AnchorX = 0.5f;
	OSDev->m_AnchorY = 0.5f;
	OSDev->m_ScaleX = 0.4f;
	OSDev->m_ScaleY = 0.4f;
	AddChild(OSDev);

	// On-Screen - Name: George
	float y_posOSG = (float)IwGxGetScreenHeight() * 0.4f;
	OSG = new CSprite();
	OSG->SetImage(g_pResources->getAbout_George());
	OSG->m_X = IwGxGetScreenWidth() / 2.0f;
	OSG->m_Y = y_posOSG;
	OSG->m_W = OSG->GetImage()->GetWidth();
	OSG->m_H = OSG->GetImage()->GetHeight();
	OSG->m_AnchorX = 0.5f;
	OSG->m_AnchorY = 0.5f;
	OSG->m_ScaleX = 0.3f;
	OSG->m_ScaleY = 0.3f;
	AddChild(OSG);

	// On-Screen - Name: Henry
	float y_posOSH = (float)IwGxGetScreenHeight() * 0.5f;
	OSH = new CSprite();
	OSH->SetImage(g_pResources->getAbout_Henry());
	OSH->m_X = IwGxGetScreenWidth() / 2.0f;
	OSH->m_Y = y_posOSH;
	OSH->m_W = OSH->GetImage()->GetWidth();
	OSH->m_H = OSH->GetImage()->GetHeight();
	OSH->m_AnchorX = 0.5f;
	OSH->m_AnchorY = 0.5f;
	OSH->m_ScaleX = 0.3f;
	OSH->m_ScaleY = 0.3f;
	AddChild(OSH);

	// On-Screen - Name: Robert
	float y_posOSR = (float)IwGxGetScreenHeight() * 0.6f;
	OSR = new CSprite();
	OSR->SetImage(g_pResources->getAbout_Robert());
	OSR->m_X = IwGxGetScreenWidth() / 2.0f;
	OSR->m_Y = y_posOSR;
	OSR->m_W = OSR->GetImage()->GetWidth();
	OSR->m_H = OSR->GetImage()->GetHeight();
	OSR->m_AnchorX = 0.5f;
	OSR->m_AnchorY = 0.5f;
	OSR->m_ScaleX = 0.3f;
	OSR->m_ScaleY = 0.3f;
	AddChild(OSR);

	// On-Screen - Note 1
	float y_posOSN1 = (float)IwGxGetScreenHeight() * 0.75f;
	OSNote1 = new CSprite();
	OSNote1->SetImage(g_pResources->getAbout_NoteMobile());
	OSNote1->m_X = IwGxGetScreenWidth() / 2.0f;
	OSNote1->m_Y = y_posOSN1;
	OSNote1->m_W = OSNote1->GetImage()->GetWidth();
	OSNote1->m_H = OSNote1->GetImage()->GetHeight();
	OSNote1->m_AnchorX = 0.5f;
	OSNote1->m_AnchorY = 0.5f;
	OSNote1->m_ScaleX = 0.6f;
	OSNote1->m_ScaleY = 0.6f;
	AddChild(OSNote1);

	// On-Screen - Note 2
	float y_posOSN2 = (float)IwGxGetScreenHeight() * 0.8f;
	OSNote2 = new CSprite();
	OSNote2->SetImage(g_pResources->getAbout_NoteSHU());
	OSNote2->m_X = IwGxGetScreenWidth() / 2.0f;
	OSNote2->m_Y = y_posOSN2;
	OSNote2->m_W = OSNote2->GetImage()->GetWidth();
	OSNote2->m_H = OSNote2->GetImage()->GetHeight();
	OSNote2->m_AnchorX = 0.5f;
	OSNote2->m_AnchorY = 0.5f;
	OSNote2->m_ScaleX = 0.6f;
	OSNote2->m_ScaleY = 0.6f;
	AddChild(OSNote2);

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