#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;
class Resources
{
protected:
	// Main Menu
	CIw2DImage*     MenuButton;
	CIw2DImage*		MenuButtonPressed;
	CIw2DImage*     PlayButton;
	CIw2DImage*		AboutButton;
	CIw2DImage*		SettingsButton;

	// Buttons
	CIw2DImage*		aboutImage;
	CIw2DImage*		settingImage;
	CIw2DImage*		pauseMenuImage;
	CIw2DImage*		continueImage;
	CIw2DImage*		gameoverImage;
	CIw2DImage*		conPlay;

	// About Menu
	CIw2DImage*		about_Developers;
	CIw2DImage*		about_George;
	CIw2DImage*		about_Henry;
	CIw2DImage*		about_Robert;
	CIw2DImage*		about_NoteMobile;
	CIw2DImage*		about_NoteSHU;

	// Settings Menu
	CIw2DImage*		muteButton;

	// Shapes
	CIw2DImage*		gameBowieStar;
	CIw2DImage*		gameCircle;
	CIw2DImage*		gameHexagon;
	CIw2DImage*		gameSquare;
	CIw2DImage*		gameTriangle;

	// Game
	CIw2DImage*		distanceImage;
	CIw2DImage*		scoreImage;
	CIw2DImage*		pauseImage;

	CIw2DImage*		coinImage;

	CIw2DImage*     PauseIcon;
	CIw2DImage*     ContinueGameButton;
	//CIw2DImage*     NewGameButton;

	// Level Objects
	CIw2DImage*		gameFloorConcept1A;
	CIw2DImage*		gameFloorConcept1FR;
	CIw2DImage*		gameFloorConcept1FL;

	// Obstacle Block
	CIw2DImage*		gameBlock01;
	CIw2DImage*		gameBlock02;
	CIw2DImage*		gameBlock03;

	// THE ACTUAL LEVEL OBJECT OBSTACLE BLOCKS
	CIw2DImage*		levelScore001;
	CIw2DImage*		levelGate001;

	CIw2DImage*		levelBlock001;
	CIw2DImage*		levelBlock001clear;

	CIw2DImage*		levelBlock001A1; // |``
	CIw2DImage*		levelBlock001A2; // ``|
	CIw2DImage*		levelBlock001A3; // |__
	CIw2DImage*		levelBlock001A4; // __|

	CIw2DImage*		levelBlock001B1; // =
	CIw2DImage*		levelBlock001B2; // | |

	CIw2DImage*		levelBlock001C1; // |``|
	CIw2DImage*		levelBlock001C2; // |__|
	CIw2DImage*		levelBlock001C3; // |=
	CIw2DImage*		levelBlock001C4; // =|

	CIw2DImage*		levelBlock001D1; // ``
	CIw2DImage*		levelBlock001D2; // __
	CIw2DImage*		levelBlock001D3; // |
	CIw2DImage*		levelBlock001D4; //   |
	
	CIw2DImage*		levelBlock001E;  // : :
	CIw2DImage*		levelBlock001G2; // . .

	// Misc.
	CIw2DImage*		Logo;
	CIw2DImage*		soundMute;
	CIw2DFont*      Font;

public:
	// Main Menu
	CIw2DImage*     getMenuButton()				{ return MenuButton; }
	CIw2DImage*		getMBPressed()				{ return MenuButtonPressed; }
	CIw2DImage*     getPlayButton()				{ return PlayButton; }
	CIw2DImage*		getAboutButton()			{ return AboutButton; }
	CIw2DImage*		getSettingsButton()			{ return SettingsButton; }

	// Buttons
	CIw2DImage*		getAboutImage()				{ return aboutImage; }
	CIw2DImage*		getSettingImage()			{ return settingImage; }
	CIw2DImage*		getPauseMenuImage()			{ return pauseMenuImage; }
	CIw2DImage*		getContinueImage()			{ return continueImage; }
	CIw2DImage*		getGameoverImage()			{ return gameoverImage; }
	CIw2DImage*		getConPlay()				{ return conPlay; }

	// About Menu
	CIw2DImage*		getAbout_Developers()		{ return about_Developers; }
	CIw2DImage*		getAbout_George()			{ return about_George; }
	CIw2DImage*		getAbout_Henry()			{ return about_Henry; }
	CIw2DImage*		getAbout_Robert()			{ return about_Robert; }
	CIw2DImage*		getAbout_NoteMobile()		{ return about_NoteMobile; }
	CIw2DImage*		getAbout_NoteSHU()			{ return about_NoteSHU; }

	// Settings Menu
	CIw2DImage*		getMuteButton()				{ return muteButton; }

	// Shapes
	CIw2DImage*		getGameBowieStar()			{ return gameBowieStar; }
	CIw2DImage*		getGameCircle()				{ return gameCircle; }
	CIw2DImage*		getGameHexagon()			{ return gameHexagon; }
	CIw2DImage*		getGameSquare()				{ return gameSquare; }
	CIw2DImage*		getGameTriangle()			{ return gameTriangle; }

	// Game
	CIw2DImage*		getDistanceImage()			{ return distanceImage; }
	CIw2DImage*		getScoreImage()				{ return scoreImage; }
	CIw2DImage*     getPauseImage()				{ return pauseImage; }

	CIw2DImage*		getCoinImage()				{ return coinImage; }

	CIw2DImage*     getPauseIcon()				{ return PauseIcon; }
	CIw2DImage*     getContinueGameButton()		{ return MenuButton; }

	// Level Objects
	CIw2DImage*     getGameFloorConcept1A()		{ return gameFloorConcept1A; }
	CIw2DImage*     getGameFloorConcept1FR()	{ return gameFloorConcept1FR; }
	CIw2DImage*     getGameFloorConcept1FL()	{ return gameFloorConcept1FL; }

	// Obstacle Block
	CIw2DImage*		getGameBlock01()			{ return gameBlock01; }
	CIw2DImage*		getGameBlock02()			{ return gameBlock02; }
	CIw2DImage*		getGameBlock03()			{ return gameBlock03; }

	// THE ACTUAL LEVEL OBJECT OBSTACLE BLOCKS
	CIw2DImage*		getLevelScore001()			{ return levelScore001; }
	CIw2DImage*		getLevelGate001()			{ return levelGate001; }

	CIw2DImage*		getLevelBlock001()			{ return levelBlock001; }
	CIw2DImage*		getLevelBlock001clear()		{ return levelBlock001clear; }

	CIw2DImage*		getLevelBlock001A1()		{ return levelBlock001A1; } // |``
	CIw2DImage*		getLevelBlock001A2()		{ return levelBlock001A2; } // ``|
	CIw2DImage*		getLevelBlock001A3()		{ return levelBlock001A3; } // |__
	CIw2DImage*		getLevelBlock001A4()		{ return levelBlock001A4; } // __|

	CIw2DImage*		getLevelBlock001B1()		{ return levelBlock001B1; } // =
	CIw2DImage*		getLevelBlock001B2()		{ return levelBlock001B2; } // | |

	CIw2DImage*		getLevelBlock001C1()		{ return levelBlock001C1; } // |``|
	CIw2DImage*		getLevelBlock001C2()		{ return levelBlock001C2; } // |__|
	CIw2DImage*		getLevelBlock001C3()		{ return levelBlock001C3; } // |=
	CIw2DImage*		getLevelBlock001C4()		{ return levelBlock001C4; } // =|

	CIw2DImage*		getLevelBlock001D1()		{ return levelBlock001D1; } // ``
	CIw2DImage*		getLevelBlock001D2()		{ return levelBlock001D2; } // __
	CIw2DImage*		getLevelBlock001D3()		{ return levelBlock001D3; } // |
	CIw2DImage*		getLevelBlock001D4()		{ return levelBlock001D4; } //   |
	
	CIw2DImage*		getLevelBlock001E()			{ return levelBlock001E;  } // : :
	CIw2DImage*		getLevelBlock001G2()		{ return levelBlock001G2; } // . .

	// Misc.
	CIw2DImage*		getLogo()					{ return Logo; }
	CIw2DImage*		getSoundMute()				{ return soundMute; }
	CIw2DFont*      getFont()                   { return Font; }

public:
	Resources();
	~Resources();
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__