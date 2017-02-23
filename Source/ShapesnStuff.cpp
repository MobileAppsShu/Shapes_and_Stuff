#include "s3e.h"
#include "IwDebug.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"

#include "input.h"
#include "scene.h"
#include "resources.h"
#include "mainMenu.h"
#include "about.h"
#include "settings.h"
#include "audio.h"
#include "game.h"
#include "pauseMenu.h"
#include "gameoverMenu.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (30.0f / 1000.0f)


// Main entry point for the application
int main()
{
	// Initialise the 2D graphics system
	Iw2DInit();

	// Create resources
	g_pResources = new Resources();

	// Set up input systems
	g_pInput = new Input();

	// Set up audio systems
	g_pAudio = new Audio();

	// Create scene manager
	g_pSceneManager = new SceneManager();

	// Init - Game
	Game* game = new Game();
	game->SetName("game");
	game->Init();
	g_pSceneManager->Add(game);
	game->newGame();

	// Init - Main Menu
	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	// Init - About Menu
	About* about_menu = new About();
	about_menu->SetName("aboutmenu");
	about_menu->Init();
	g_pSceneManager->Add(about_menu);

	// Init - Settings Menu
	Settings* settings_menu = new Settings();
	settings_menu->SetName("settingsmenu");
	settings_menu->Init();
	g_pSceneManager->Add(settings_menu);

	// Init - Pause Menu
	PauseMenu* pause_menu = new PauseMenu();
	pause_menu->SetName("pausemenu");
	pause_menu->Init();
	g_pSceneManager->Add(pause_menu);
	
	// Init - Game Over Menu
	GameOverMenu* gameover_menu = new GameOverMenu();
	gameover_menu->SetName("gameovermenu");
	gameover_menu->Init();
	g_pSceneManager->Add(gameover_menu);

	// Switch to main menu scene
	g_pSceneManager->SwitchTo(main_menu);

	// Loop forever, until the user or the OS performs some action to quit the app
	while (!s3eDeviceCheckQuitRequest())
	{
		// Update input system
		g_pInput->Update();

		// Clear the screen
		CIwColour screenColour;
		screenColour.Set(0x3B, 0x98, 0xEB); // Red, Green, Blue
		Iw2DSurfaceClear(screenColour);

		// Update scene manager
		g_pSceneManager->Update(FRAME_TIME);

		// Clear the drawing surface
		//Iw2DSurfaceClear(0xff000000);

		// Render scene manager
		g_pSceneManager->Render();

		// Show the drawing surface
		Iw2DSurfaceShow();

		// Yield to the OS
		s3eDeviceYield(0);
	}

	// Clean-up
	delete g_pInput;
	delete g_pSceneManager;
	delete g_pResources;
	delete g_pAudio;
	Iw2DTerminate();

	return 0;
}
