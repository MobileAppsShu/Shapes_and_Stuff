#if !defined(__GAME_H__)
#define __GAME_H__

#include "scene.h"

/**
* @enum  eGameState
*
* @brief List of game states.
*/
enum eGameState
{
	paused = 0,		// The game is paused
	play = 1,		// The game is playing
	roundOver = 2,  // The game round is over
};

class Game : public Scene
{
protected:
	int                 currentRoundScore;              // Current round score
	eGameState          gameState;                      // Current game state
	eGameState          oldGameState;                   // Previous game state

	// UI components
	CLabel*             scoreLabel;
	CSprite*            pauseSprite;
	CSprite*            gemSprite;
	CSprite*			ScoreImage;
	CSprite*			DistanceImage;
	CSprite*			Floor1A;
	CSprite*			Floor1FR[100];
	CSprite*			Floor1FL;

	CSprite*			Block1;
	CSprite*			Block2[100];
	CSprite*			Block3;

	CSprite*			Coin1[100];
	CSprite*			Gate1[100];
	
	CSprite*            GameSquare;
	
	// LEVEL 01
	CSprite*			Block01[100];
	CSprite*			BlockA1[100];
	CSprite*			BlockA2[100];
	CSprite*			BlockA3[100];
	CSprite*			BlockA4[100];
	CSprite*			BlockB1[100];
	CSprite*			BlockB2[100];
	CSprite*			BlockC1[100];
	CSprite*			BlockC2[100];
	CSprite*			BlockC3[100];
	CSprite*			BlockC4[100];
	CSprite*			BlockD1[100];
	CSprite*			BlockD2[100];
	CSprite*			BlockE[100];
	CSprite*			BlockG2[100];



private:
	void            initUI();
	void			initLevel();
	void			bigShapeCollision(int jj);
	void			smallShapeCollision(int ii);
	void			bigShapeScore(int jj);
public:
	Game() {}
	~Game();

	// initialise the game
	void    Init();
	void	Nplaying();
	void	Yplaying();
	void	scrollJetpackMap(int);
	void	resetGame();

	void	loopDrawImage(int);
	void	gravityDraw(int);
	bool	a = false;
	int		bt = 0;
	bool	b = false;
	bool	gravity = true;
	bool	Playing = false;
	bool	jumped = true;

	float smallHeight;
	float smallWidth;
	float bigHeight;
	float bigWidth;

	int powerup = 0;

	// Update the game
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the game
	void            Render();
	void			gamePower();
	void			gamePowerII();
	void			gamePowerCollision();
	void			jumpPower();
	void			gravityPower();
	void			lanePower();
	void			jetPackPower();
	void			jumpMap();
	void			gravityMap();
	void			laneMap();
	void			jetPackMap();

	void            switchToScene(const char* scene_name);
	void            addToRoundScore(int score, int jj);
	void            pauseGame();
	void            resumeGame();
	void            newGame();
	void			gameoverGame();
	void			initRound();
	void			endOfRound();
	void			laneLVL1();
	void			laneLEVEL01();

	void            changeGameState(eGameState game_state);

};


#endif  // __GAME_H__