#if !defined(__PAUSEMENU_H__)
#define __PAUSEMENU_H__

#include "scene.h"

class PauseMenu : public Scene
{
protected:
	// UI components
	CSprite*    conPlay;
	CSprite*    newGameButton;
	CSprite*	menuButton;
	CSprite*	pauseMenu;
	CSprite*	muteButton;

	CSprite*	ShapesSquare;
	CSprite*	ShapesTriangle;
	CSprite*	ShapesHexagon;
	CSprite*	ShapesCircle;

public:
	CSprite*    getConGameButton()			{ return conPlay; }
	CSprite*    getNewGameButton()          { return newGameButton; }
	CSprite*    getMenuButton()				{ return menuButton; }
	//CSprite*	getConImage()				{ return conImage; }

public:
	PauseMenu() {}
	~PauseMenu();

	// initialise the menu
	void            Init();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();

};

#endif  // __PAUSEMENU_H__