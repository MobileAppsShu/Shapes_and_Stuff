#if !defined(__MAINEMENU_H__)
#define __MAINEMENU_H__

#include "scene.h"

class MainMenu : public Scene
{
protected:
	// UI components
	CSprite*    playButton;
	CSprite*	aboutButton;
	CSprite*	settingsButton;
	CSprite*	ShapesSquare;
	CSprite*	ShapesTriangle;
	CSprite*	ShapesStar;
	CSprite*	ShapesHexagon;
	CSprite*	ShapesCircle;
	CSprite*	logo;
	CSprite*	soundMute;
	//CSprite*    playText;

public:
	MainMenu() {}
	~MainMenu();

	// initialise the menu
	void            Init();
	void			initBackUI();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();
	void			aboutGame();
};

#endif  // __MAINEMENU_H__