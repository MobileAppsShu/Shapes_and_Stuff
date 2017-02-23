
#include "s3e.h"
#include "IwDebug.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"

#include "input.h"
#include "scene.h"
#include "resources.h"
#include "mainMenu.h"

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

	// Create scene manager
	g_pSceneManager = new SceneManager();

	// Init the main menu
	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	// Switch to main menu scene
	g_pSceneManager->SwitchTo(main_menu);

	// Loop forever, until the user or the OS performs some action to quit the app
	while (!s3eDeviceCheckQuitRequest())
	{
		// Update input system
		g_pInput->Update();

		// Update scene manager
		g_pSceneManager->Update(FRAME_TIME);

		// Clear the drawing surface
		Iw2DSurfaceClear(0xff000000);

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
	Iw2DTerminate();

	return 0;
}
