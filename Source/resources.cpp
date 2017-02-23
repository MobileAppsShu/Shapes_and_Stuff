#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
	// ~ Load Images ~

	// Main Menu
	MenuButton = Iw2DCreateImage("textures/Menu_Button_Gradient.png");
	MenuButtonPressed = Iw2DCreateImage("textures/Menu_Button_Inverted.png");
	PlayButton = Iw2DCreateImage("textures/Play_Button_Gradient.png");
	AboutButton = Iw2DCreateImage("textures/About_Button_Gradient.png");
	SettingsButton = Iw2DCreateImage("textures/Settings_Button_Gradient.png");

	// Buttons
	aboutImage = Iw2DCreateImage("textures/AboutUs_Logo.png");
	settingImage = Iw2DCreateImage("textures/Settings_Logo.png");
	pauseMenuImage = Iw2DCreateImage("textures/PauseMenu_Logo.png");
	continueImage = Iw2DCreateImage("textures/Continue_Logo.png");
	gameoverImage = Iw2DCreateImage("textures/GameOver_Logo.png");
	conPlay = Iw2DCreateImage("textures/Play_Button_Gradient.png");

	// About Menu
	about_Developers = Iw2DCreateImage("textures/About_Developers.png");
	about_George = Iw2DCreateImage("textures/About_George.png");
	about_Henry = Iw2DCreateImage("textures/About_Henry.png");
	about_Robert = Iw2DCreateImage("textures/About_Robert.png");
	about_NoteMobile = Iw2DCreateImage("textures/AboutNote_MobileApp.png");
	about_NoteSHU = Iw2DCreateImage("textures/AboutNote_SHU.png");

	// Settings Menu
	muteButton = Iw2DCreateImage("textures/Settings_MuteI.png");

	// Shapes
	gameBowieStar = Iw2DCreateImage("textures/BowieStar.png");
	gameCircle = Iw2DCreateImage("textures/Circle.png");
	gameHexagon = Iw2DCreateImage("textures/Hexagon.png");
	gameSquare = Iw2DCreateImage("textures/Square.png");
	gameTriangle = Iw2DCreateImage("textures/Triangle.png");

	// Game
	distanceImage = Iw2DCreateImage("textures/Distance_Inverted.png");
	scoreImage = Iw2DCreateImage("textures/Score_Inverted.png");
	pauseImage = Iw2DCreateImage("textures/Pause_Gradient.png");

	coinImage = Iw2DCreateImage("textures/coin1.png");

	PauseIcon = Iw2DCreateImage("textures/pause_icon.png");
	ContinueGameButton = Iw2DCreateImage("textures/Continue_Button_Gradient.png");

	// Level Objects
	gameFloorConcept1A = Iw2DCreateImage("textures/Floor_Concept_1B.png");
	gameFloorConcept1FR = Iw2DCreateImage("textures/Floor_Concept_1F_RightSide.png");
	gameFloorConcept1FL = Iw2DCreateImage("textures/Floor_Concept_1F_LeftSide.png");

	// Obstacle Block
	gameBlock01 = Iw2DCreateImage("textures/block01.png");
	gameBlock02 = Iw2DCreateImage("textures/block02.png");
	gameBlock03 = Iw2DCreateImage("textures/block03.png");

	// THE ACTUAL LEVEL OBJECT OBSTACLE BLOCKS
	levelScore001 = Iw2DCreateImage("textures/score001.png");
	levelGate001 = Iw2DCreateImage("textures/gate001.png");

	levelBlock001 = Iw2DCreateImage("textures/block001.png");
	levelBlock001clear = Iw2DCreateImage("textures/block001clear.png");

	levelBlock001A1 = Iw2DCreateImage("textures/block001A1.png"); // |``
	levelBlock001A2 = Iw2DCreateImage("textures/block001A2.png"); // ``|
	levelBlock001A3 = Iw2DCreateImage("textures/block001A3.png"); // |__
	levelBlock001A4 = Iw2DCreateImage("textures/block001A4.png"); // __|

	levelBlock001B1 = Iw2DCreateImage("textures/block001B1.png"); // =
	levelBlock001B2 = Iw2DCreateImage("textures/block001B2.png"); // | |

	levelBlock001C1 = Iw2DCreateImage("textures/block001C1.png"); // |``|
	levelBlock001C2 = Iw2DCreateImage("textures/block001C2.png"); // |__|
	levelBlock001C3 = Iw2DCreateImage("textures/block001C3.png"); // |=
	levelBlock001C4 = Iw2DCreateImage("textures/block001C4.png"); // =|

	levelBlock001D1 = Iw2DCreateImage("textures/block001D1.png"); // ``
	levelBlock001D2 = Iw2DCreateImage("textures/block001D2.png"); // __
	levelBlock001D3 = Iw2DCreateImage("textures/block001D3.png"); // |
	levelBlock001D4 = Iw2DCreateImage("textures/block001D4.png"); //   |
	
	levelBlock001E = Iw2DCreateImage("textures/block001E.png");   // : :
	levelBlock001G2 = Iw2DCreateImage("textures/block001G2.png"); // . .

	// Misc.
	Logo = Iw2DCreateImage("textures/SNS_Logo.png");			// Logo
	soundMute = Iw2DCreateImage("textures/pause_icon.png");		// Sound
	Font = Iw2DCreateFont("fonts/arial8.gxfont");				// Font
}

Resources::~Resources()
{
	// Main Menu
	delete MenuButton;
	delete MenuButtonPressed;
	delete PlayButton;
	delete AboutButton;
	delete SettingsButton;

	// Buttons
	delete aboutImage;
	delete settingImage;
	delete pauseMenuImage;
	delete continueImage;
	delete gameoverImage;
	delete conPlay;

	// About Menu
	delete about_Developers;
	delete about_George;
	delete about_Henry;
	delete about_Robert;
	delete about_NoteMobile;
	delete about_NoteSHU;

	// Settings Menu
	delete muteButton;

	// Shapes
	delete gameBowieStar;
	delete gameCircle;
	delete gameHexagon;
	delete gameSquare;
	delete gameTriangle;

	// Game
	delete distanceImage;
	delete scoreImage;
	delete pauseImage;

	delete coinImage;

	delete PauseIcon;
	delete ContinueGameButton;
	
	// Level Objects
	delete gameFloorConcept1A;
	delete gameFloorConcept1FR;
	delete gameFloorConcept1FL;

	// Obstacle Block
	delete gameBlock01;
	delete gameBlock02;
	delete gameBlock03;

	// THE ACTUAL LEVEL OBJECT OBSTACLE BLOCKS
	delete levelScore001;
	delete levelGate001;

	delete levelBlock001;
	delete levelBlock001clear;

	delete levelBlock001A1; // |``
	delete levelBlock001A2; // ``|
	delete levelBlock001A3; // |__
	delete levelBlock001A4; // __|

	delete levelBlock001B1; // =
	delete levelBlock001B2; // | |

	delete levelBlock001C1; // |``|
	delete levelBlock001C2; // |__|
	delete levelBlock001C3; // |=
	delete levelBlock001C4; // =|

	delete levelBlock001D1; // ``
	delete levelBlock001D2; // __
	delete levelBlock001D3; // |
	delete levelBlock001D4; //   |
	
	delete levelBlock001E;  // : :
	delete levelBlock001G2; // . .

	// Misc.
	delete Logo;
	delete soundMute;
	delete Font;
}

// Global resources
Resources* g_pResources = 0;