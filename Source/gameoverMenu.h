#if !defined(__GAMEOVERMENU_H__)
#define __GAMEOVERMENU_H__

#include "scene.h"

class GameOverMenu : public Scene
{
protected:
	// UI components
	CSprite*    conPlay;
	CSprite*	menuButton;
	CSprite*	gameoverImage;

	CSprite*	ShapesSquare;
	CSprite*	ShapesTriangle;
	CSprite*	ShapesStar;
	CSprite*	ShapesHexagon;
	CSprite*	ShapesCircle;
public:
	CSprite*    getConGameButton()          { return conPlay; }
	CSprite*    getMenuButton()				{ return menuButton; }
	CSprite*	gameOverLogo()				{ return gameoverImage; }
public:
	GameOverMenu() {}
	~GameOverMenu();

	// initialise the menu
	void            Init();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();

};

#endif  // __GAMEOVERMENU_H__