#if !defined(__SETTINGS_H__)
#define __SETTINGS_H__

#include "scene.h"

class Settings : public Scene
{
protected:
	// UI components
	CSprite*	settingImage;
	CSprite*	menuButton;
	
	CSprite*	ShapesTriangle;
	CSprite*	muteButton;
	CSprite*	ShapesHexagon;

public:
	Settings() {}
	~Settings();

	// initialise the menu
	void            Init();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();
};

#endif  // __MAINEMENU_H__