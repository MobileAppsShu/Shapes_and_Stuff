#if !defined(__ABOUT_H__)
#define __ABOUT_H__

#include "scene.h"

class About : public Scene
{
protected:
	// UI components
	CSprite*	aboutImage;
	CSprite*    playButton;
	CSprite*	menuButton;
	CSprite*	menuButtonPressed;
	CSprite*	settingsButton;

	CSprite*	OSDev;
	CSprite*	OSG;
	CSprite*	OSH;
	CSprite*	OSR;
	CSprite*	OSNote1;
	CSprite*	OSNote2;

	CSprite*	ShapesSquare;
	CSprite*	ShapesCircle;

public:
	About() {}
	~About();

	// initialise the menu
	void            Init();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();
	void			menuGame();
};

#endif  // __MAINEMENU_H__