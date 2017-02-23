#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "input.h"
#include "audio.h"
#include "pauseMenu.h"
#include "resources.h"

Game::~Game()
{
}

void Game::pauseGame()
{
	// Switch to pause menu scene
	g_pSceneManager->SwitchTo(g_pSceneManager->Find("pausemenu"));
}

void Game::resumeGame()
{
}

void Game::newGame()
{
	//initRound();
}

void Game::gameoverGame()
{
	// Switch to game over menu scene
	g_pSceneManager->SwitchTo(g_pSceneManager->Find("gameovermenu"));
}

// Add to round score
void Game::addToRoundScore(int score, int jj)
{
	currentRoundScore += score;

	char str[16];
	snprintf(str, 16, "%d", currentRoundScore);
	scoreLabel->m_Text = str;
}

// Initialise a round
void Game::initRound()
{
	// Reset round score
	currentRoundScore = 0;

	// Set up labels
	char str[32];
	snprintf(str, 32, "%d", currentRoundScore);
	scoreLabel->m_Text = str;
}

void Game::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	if (Playing)
	{
		// Update base scene
		Scene::Update(deltaTime, alphaMul);

		// Detect screen tap
		if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			bt = 0;
			a = true;
			if (gravity == true)
			{
				gravity = false;

			}
			else if (gravity == false)
			{
				gravity = true;
			}

			// Reset input
			g_pInput->Reset();


			//testing button to switch between powers by clicking on score
			if (ScoreImage->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				gamePower();
			}
			if (DistanceImage->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				resetGame();
			}

			// Detect Pause Button
			if (pauseSprite->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				Nplaying();

				// Enter pause menu
				pauseGame();
			}
			gamePowerII();
		}
		gamePowerCollision();
	}
}

// Power-ups
void Game::gamePower()
{
	if (powerup == 0)
	{
		//sorts out level for lane
		laneMap();
		powerup = 1;

	}
	else if (powerup == 1)
	{
		//sorts out level for gravity
		gravityMap();

		powerup = 2;
	}
	else if (powerup == 2)
	{
		//sorts out level for jump
		jumpMap();

		powerup = 3;
	}

	else if (powerup == 3)
	{
		//sorts out level for jetpack
		
		jetPackMap();


		powerup = 0;
	}
}

void Game::gamePowerII()
{
	if (powerup == 3 && GameSquare->m_Y >= (float)IwGxGetScreenHeight() - ((float)IwGxGetScreenHeight() / 3))
	{
		jumped = true;
	}
	if (powerup == 1)
	{
		lanePower();
	}
}

// Colliding code
void Game::gamePowerCollision()
{
	if (powerup == 0)
	{
		Block1->m_Y = -500;
		Block2[1]->m_Y = -500;
		Block3->m_Y = -500;

		jetPackPower();
	}
	if (powerup == 2)
	{
		gravityPower();
		//this function moves the map with the number increasing the speed
		scrollJetpackMap(-6);
		for (int i = 0; i < 50; i++)
		{
			bigShapeCollision(i);
		}
		//this is the collision between the shapes in the gravity powerup
		smallShapeCollision(26);
		smallShapeCollision(27);
	}
	if (powerup == 3)
	{
		jumpPower();
	}
	if (powerup == 1)
	{
		Block1->m_Y = -500;
		Block2[1]->m_Y = -500;
		Block3->m_Y = -500;

		scrollJetpackMap(-6);
		//this sorts the collision for the lanes
		for (int i = 0; i < 50; i++)
		{
			bigShapeCollision(i);
		}
	}
}

void Game::lanePower()
{
	//Movement for the lane power
	if (g_pInput->m_Y < (float)IwGxGetScreenHeight() / 2.2f)
	{
		GameSquare->m_Y = (float)IwGxGetScreenHeight() / 5;
	}
	if (g_pInput->m_Y < (float)IwGxGetScreenHeight() / 1.4f && g_pInput->m_Y >= (float)IwGxGetScreenHeight() / 2.2f)
	{
		GameSquare->m_Y = 2.5f * ((float)IwGxGetScreenHeight() / 5);
	}
	if (g_pInput->m_Y >= (float)IwGxGetScreenHeight() / 1.4f)
	{
		Block1->m_Y = -500;
		GameSquare->m_Y = 4 * ((float)IwGxGetScreenHeight() / 5);
	}
}

void Game::jumpPower()
{
	scrollJetpackMap(-8);

	//Movement for jump power
	smallShapeCollision(27);
	if (GameSquare->m_Y <= (float)IwGxGetScreenHeight() / 2)
	{
		jumped = false;
	}

	if (jumped)
	{
		loopDrawImage(-4);
	}
	if (!jumped)
	{
		loopDrawImage(4);
	}
}

void Game::jetPackPower()
{
	scrollJetpackMap(-3);

	//jetpack collision below
	bigShapeCollision(2);
	smallShapeCollision(26);


	//jetpack movement is below
	if (a == false)
	{
		bt++;
		if (bt < 3)
		{
			loopDrawImage(4);
		}
		else if (bt > 2 && bt < 5)
		{
			loopDrawImage(8);
		}
		else if (bt > 4)
		{
			loopDrawImage(10);
		}
	}
	if (bt < 10 && a)
	{
		loopDrawImage(-4);
		bt++;
	}
	else
	{
		a = false;
		bt = 0;
	}
}

void Game::gravityPower()
{
	//gravity movement below
	if (gravity == true)
	{
		gravityDraw(-10);
	}
	if (gravity == false)
	{
		gravityDraw(10);
	}
}

void Game::Render()
{
	Scene::Render();
}

// Initialise the games user interface
void Game::initUI()
{
	// Create pause menu sprite (docked to top of screen)
	pauseSprite = new CSprite();
	pauseSprite->SetImage(g_pResources->getPauseImage());
	pauseSprite->m_X = (float)IwGxGetScreenWidth() / 2;
	pauseSprite->m_Y = 50.0f;
	pauseSprite->m_W = pauseSprite->GetImage()->GetWidth();
	pauseSprite->m_H = pauseSprite->GetImage()->GetHeight();
	pauseSprite->m_AnchorX = 0.5;
	pauseSprite->m_ScaleX = 0.75f;
	pauseSprite->m_ScaleY = 0.75f;
	AddChild(pauseSprite);

	// Create score label text
	CLabel* scoreLabelText = new CLabel();
	scoreLabelText->m_X = 10;
	scoreLabelText->m_Y = 0;
	scoreLabelText->m_W = (float)IwGxGetScreenWidth();
	scoreLabelText->m_H = 30;
	scoreLabelText->m_Text = "Score:";
	scoreLabelText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	scoreLabelText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	scoreLabelText->m_Font = g_pResources->getFont();
	scoreLabelText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
	AddChild(scoreLabelText);

	// Create score label (displays actual score)
	scoreLabel = new CLabel();
	scoreLabel->m_X = 80;
	scoreLabel->m_Y = 0;
	scoreLabel->m_W = (float)IwGxGetScreenWidth();
	scoreLabel->m_H = 30;
	scoreLabel->m_Text = "0";
	scoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	scoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	scoreLabel->m_Font = g_pResources->getFont();
	scoreLabelText->m_Color = CColor(0xff, 0xff, 0xff, 0xff);
	AddChild(scoreLabel);

	GameSquare = new CSprite();
	GameSquare->SetImage(g_pResources->getCoinImage());
	GameSquare->m_X = (float)IwGxGetScreenWidth() / 3;
	GameSquare->m_Y = 0;
	GameSquare->m_W = GameSquare->GetImage()->GetWidth() ;
	GameSquare->m_H = GameSquare->GetImage()->GetHeight() ;
	GameSquare->m_AnchorX = 0.5f;
	GameSquare->m_AnchorY = 0.5f;
	AddChild(GameSquare);
}

void Game::initLevel() // Height = 750 | Width = 1334
{
	// Create Block 01
	float x_posBlock1 = (float)IwGxGetScreenWidth() * 0.0f;
	float y_posBlock1 = (float)IwGxGetScreenHeight() * 0.8f;
	Block1 = new CSprite();
	Block1->SetImage(g_pResources->getGameBlock01());
	Block1->m_X = x_posBlock1;
	Block1->m_Y = y_posBlock1;
	Block1->m_W = Block1->GetImage()->GetWidth();
	Block1->m_H = Block1->GetImage()->GetHeight();
	Block1->m_AnchorX = 0.0f;
	Block1->m_AnchorY = 0.0f;
	Block1->m_ScaleX = 1.5f;
	Block1->m_ScaleY = 1.5f;
	AddChild(Block1);

	// Create Block 02
	float x_posBlock2 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlock2 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		Block2[i] = new CSprite();
		Block2[i]->SetImage(g_pResources->getLevelBlock001());
		Block2[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		Block2[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		Block2[i]->m_W = Block2[i]->GetImage()->GetWidth();
		Block2[i]->m_H = Block2[i]->GetImage()->GetHeight();
		Block2[i]->m_AnchorX = 0.5f;
		Block2[i]->m_AnchorY = 0.5f;
		Block2[i]->m_ScaleX = 1.0f;
		Block2[i]->m_ScaleY = 1.0f;
		AddChild(Block2[i]);

	}
	Block2[1]->m_X = x_posBlock2;
	Block2[1]->m_Y = y_posBlock2;
	Block2[2]->m_X = (float)IwGxGetScreenWidth() * 0.56f;
	Block2[2]->m_Y = (float)IwGxGetScreenHeight() / 3;

	// Create Block 03
	float x_posBlock3 = (float)IwGxGetScreenWidth() * 0.89f;
	float y_posBlock3 = (float)IwGxGetScreenHeight() * 0.8f;
	Block3 = new CSprite();
	Block3->SetImage(g_pResources->getGameBlock03());
	Block3->m_X = x_posBlock3;
	Block3->m_Y = y_posBlock3;
	Block3->m_W = Block3->GetImage()->GetWidth();
	Block3->m_H = Block3->GetImage()->GetHeight();
	Block3->m_AnchorX = 0.0f;
	Block3->m_AnchorY = 0.0f;
	Block3->m_ScaleX = 1.5f;
	Block3->m_ScaleY = 1.5f;
	AddChild(Block3);

	// Create Coin1
	float x_posCoin01 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posCoin01 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 25; i++)
	{
		Coin1[i] = new CSprite();
		Coin1[i]->SetImage(g_pResources->getLevelScore001());
		Coin1[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		Coin1[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		Coin1[i]->m_W = Coin1[i]->GetImage()->GetWidth();
		Coin1[i]->m_H = Coin1[i]->GetImage()->GetHeight();
		Coin1[i]->m_AnchorX = 0.5f;
		Coin1[i]->m_AnchorY = 0.5f;
		Coin1[i]->m_ScaleX = 1.0f;
		Coin1[i]->m_ScaleY = 1.0f;
		AddChild(Coin1[i]);
	}
	for (int i = 25; i < 50; i++)
	{
		Coin1[i] = new CSprite();
		Coin1[i]->SetImage(g_pResources->getLevelScore001());
		Coin1[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		Coin1[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		Coin1[i]->m_W = Coin1[i]->GetImage()->GetWidth();
		Coin1[i]->m_H = Coin1[i]->GetImage()->GetHeight();
		Coin1[i]->m_AnchorX = 0.5f;
		Coin1[i]->m_AnchorY = 0.5f;
		Coin1[i]->m_ScaleX = 0.5f;
		Coin1[i]->m_ScaleY = 0.5f;
		AddChild(Coin1[i]);
	}

	// Create Gate
	float x_posGate01 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posGate01 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 50; i++)
	{
		Gate1[i] = new CSprite();
		Gate1[i]->SetImage(g_pResources->getLevelGate001());
		Gate1[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		Gate1[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		Gate1[i]->m_W = Gate1[i]->GetImage()->GetWidth();
		Gate1[i]->m_H = Gate1[i]->GetImage()->GetHeight();
		Gate1[i]->m_AnchorX = 0.5f;
		Gate1[i]->m_AnchorY = 0.5f;
		Gate1[i]->m_ScaleX = 1.0f;
		Gate1[i]->m_ScaleY = 1.0f;
		AddChild(Gate1[i]);
	}
	
	// ########## LEVEL 01 #########
	// Create Block01
	float x_posBlock01 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlock01 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		Block01[i] = new CSprite();
		Block01[i]->SetImage(g_pResources->getLevelBlock001());
		Block01[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		Block01[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		Block01[i]->m_W = Block01[i]->GetImage()->GetWidth();
		Block01[i]->m_H = Block01[i]->GetImage()->GetHeight();
		Block01[i]->m_AnchorX = 0.5f;
		Block01[i]->m_AnchorY = 0.5f;
		Block01[i]->m_ScaleX = 1.0f;
		Block01[i]->m_ScaleY = 1.0f;
		AddChild(Block01[i]);

	}
	//Block01[1]->m_X = x_posBlock01;
	//Block01[1]->m_Y = y_posBlock01;
	//Block01[2]->m_X = (float)IwGxGetScreenWidth() * 0.56f;
	//Block01[2]->m_Y = (float)IwGxGetScreenHeight() / 3;
	
	// Create BlockA1
	float x_posBlockA1 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockA1 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockA1[i] = new CSprite();
		BlockA1[i]->SetImage(g_pResources->getLevelBlock001A1());
		BlockA1[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockA1[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockA1[i]->m_W = BlockA1[i]->GetImage()->GetWidth();
		BlockA1[i]->m_H = BlockA1[i]->GetImage()->GetHeight();
		BlockA1[i]->m_AnchorX = 0.5f;
		BlockA1[i]->m_AnchorY = 0.5f;
		BlockA1[i]->m_ScaleX = 1.0f;
		BlockA1[i]->m_ScaleY = 1.0f;
		AddChild(BlockA1[i]);
	}
	// Create BlockA2
	float x_posBlockA2 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockA2 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockA2[i] = new CSprite();
		BlockA2[i]->SetImage(g_pResources->getLevelBlock001A2());
		BlockA2[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockA2[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockA2[i]->m_W = BlockA2[i]->GetImage()->GetWidth();
		BlockA2[i]->m_H = BlockA2[i]->GetImage()->GetHeight();
		BlockA2[i]->m_AnchorX = 0.5f;
		BlockA2[i]->m_AnchorY = 0.5f;
		BlockA2[i]->m_ScaleX = 1.0f;
		BlockA2[i]->m_ScaleY = 1.0f;
		AddChild(BlockA2[i]);
	}
	// Create BlockA3
	float x_posBlockA3 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockA3 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockA3[i] = new CSprite();
		BlockA3[i]->SetImage(g_pResources->getLevelBlock001A3());
		BlockA3[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockA3[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockA3[i]->m_W = BlockA3[i]->GetImage()->GetWidth();
		BlockA3[i]->m_H = BlockA3[i]->GetImage()->GetHeight();
		BlockA3[i]->m_AnchorX = 0.5f;
		BlockA3[i]->m_AnchorY = 0.5f;
		BlockA3[i]->m_ScaleX = 1.0f;
		BlockA3[i]->m_ScaleY = 1.0f;
		AddChild(BlockA3[i]);
	}
	// Create BlockA4
	float x_posBlockA4 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockA4 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockA4[i] = new CSprite();
		BlockA4[i]->SetImage(g_pResources->getLevelBlock001A4());
		BlockA4[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockA4[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockA4[i]->m_W = BlockA4[i]->GetImage()->GetWidth();
		BlockA4[i]->m_H = BlockA4[i]->GetImage()->GetHeight();
		BlockA4[i]->m_AnchorX = 0.5f;
		BlockA4[i]->m_AnchorY = 0.5f;
		BlockA4[i]->m_ScaleX = 1.0f;
		BlockA4[i]->m_ScaleY = 1.0f;
		AddChild(BlockA4[i]);
	}
	// Create BlockB1
	float x_posBlockB1 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockB1 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockB1[i] = new CSprite();
		BlockB1[i]->SetImage(g_pResources->getLevelBlock001B1());
		BlockB1[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockB1[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockB1[i]->m_W = BlockB1[i]->GetImage()->GetWidth();
		BlockB1[i]->m_H = BlockB1[i]->GetImage()->GetHeight();
		BlockB1[i]->m_AnchorX = 0.5f;
		BlockB1[i]->m_AnchorY = 0.5f;
		BlockB1[i]->m_ScaleX = 1.0f;
		BlockB1[i]->m_ScaleY = 1.0f;
		AddChild(BlockB1[i]);
	}
	// Create BlockA2
	float x_posBlockB2 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockB2 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockB2[i] = new CSprite();
		BlockB2[i]->SetImage(g_pResources->getLevelBlock001B2());
		BlockB2[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockB2[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockB2[i]->m_W = BlockB2[i]->GetImage()->GetWidth();
		BlockB2[i]->m_H = BlockB2[i]->GetImage()->GetHeight();
		BlockB2[i]->m_AnchorX = 0.5f;
		BlockB2[i]->m_AnchorY = 0.5f;
		BlockB2[i]->m_ScaleX = 1.0f;
		BlockB2[i]->m_ScaleY = 1.0f;
		AddChild(BlockB2[i]);
	}
	// Create BlockC1
	float x_posBlockC1 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockC1 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockC1[i] = new CSprite();
		BlockC1[i]->SetImage(g_pResources->getLevelBlock001C1());
		BlockC1[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockC1[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockC1[i]->m_W = BlockC1[i]->GetImage()->GetWidth();
		BlockC1[i]->m_H = BlockC1[i]->GetImage()->GetHeight();
		BlockC1[i]->m_AnchorX = 0.5f;
		BlockC1[i]->m_AnchorY = 0.5f;
		BlockC1[i]->m_ScaleX = 1.0f;
		BlockC1[i]->m_ScaleY = 1.0f;
		AddChild(BlockC1[i]);
	}
	// Create BlockC2
	float x_posBlockC2 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockC2 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockC2[i] = new CSprite();
		BlockC2[i]->SetImage(g_pResources->getLevelBlock001C2());
		BlockC2[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockC2[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockC2[i]->m_W = BlockC2[i]->GetImage()->GetWidth();
		BlockC2[i]->m_H = BlockC2[i]->GetImage()->GetHeight();
		BlockC2[i]->m_AnchorX = 0.5f;
		BlockC2[i]->m_AnchorY = 0.5f;
		BlockC2[i]->m_ScaleX = 1.0f;
		BlockC2[i]->m_ScaleY = 1.0f;
		AddChild(BlockC2[i]);
	}
	// Create BlockC3
	float x_posBlockC3 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockC3 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockC3[i] = new CSprite();
		BlockC3[i]->SetImage(g_pResources->getLevelBlock001C3());
		BlockC3[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockC3[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockC3[i]->m_W = BlockC3[i]->GetImage()->GetWidth();
		BlockC3[i]->m_H = BlockC3[i]->GetImage()->GetHeight();
		BlockC3[i]->m_AnchorX = 0.5f;
		BlockC3[i]->m_AnchorY = 0.5f;
		BlockC3[i]->m_ScaleX = 1.0f;
		BlockC3[i]->m_ScaleY = 1.0f;
		AddChild(BlockC3[i]);
	}
	// Create BlockC4
	float x_posBlockC4 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockC4 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockC4[i] = new CSprite();
		BlockC4[i]->SetImage(g_pResources->getLevelBlock001C4());
		BlockC4[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockC4[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockC4[i]->m_W = BlockC4[i]->GetImage()->GetWidth();
		BlockC4[i]->m_H = BlockC4[i]->GetImage()->GetHeight();
		BlockC4[i]->m_AnchorX = 0.5f;
		BlockC4[i]->m_AnchorY = 0.5f;
		BlockC4[i]->m_ScaleX = 1.0f;
		BlockC4[i]->m_ScaleY = 1.0f;
		AddChild(BlockC4[i]);
	}
	// Create BlockD1
	float x_posBlockD1 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockD1 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockD1[i] = new CSprite();
		BlockD1[i]->SetImage(g_pResources->getLevelBlock001D1());
		BlockD1[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockD1[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockD1[i]->m_W = BlockD1[i]->GetImage()->GetWidth();
		BlockD1[i]->m_H = BlockD1[i]->GetImage()->GetHeight();
		BlockD1[i]->m_AnchorX = 0.5f;
		BlockD1[i]->m_AnchorY = 0.5f;
		BlockD1[i]->m_ScaleX = 1.0f;
		BlockD1[i]->m_ScaleY = 1.0f;
		AddChild(BlockD1[i]);
	}
	// Create BlockD2
	float x_posBlockD2 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockD2 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockD2[i] = new CSprite();
		BlockD2[i]->SetImage(g_pResources->getLevelBlock001D2());
		BlockD2[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockD2[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockD2[i]->m_W = BlockD2[i]->GetImage()->GetWidth();
		BlockD2[i]->m_H = BlockD2[i]->GetImage()->GetHeight();
		BlockD2[i]->m_AnchorX = 0.5f;
		BlockD2[i]->m_AnchorY = 0.5f;
		BlockD2[i]->m_ScaleX = 1.0f;
		BlockD2[i]->m_ScaleY = 1.0f;
		AddChild(BlockD2[i]);
	}

	// Create BlockE
	float x_posBlockE = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockE = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockE[i] = new CSprite();
		BlockE[i]->SetImage(g_pResources->getLevelBlock001E());
		BlockE[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockE[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockE[i]->m_W = BlockE[i]->GetImage()->GetWidth();
		BlockE[i]->m_H = BlockE[i]->GetImage()->GetHeight();
		BlockE[i]->m_AnchorX = 0.5f;
		BlockE[i]->m_AnchorY = 0.5f;
		BlockE[i]->m_ScaleX = 1.0f;
		BlockE[i]->m_ScaleY = 1.0f;
		AddChild(BlockE[i]);
	}
	// Create BlockG2
	float x_posBlockG2 = (float)IwGxGetScreenWidth() * 0.56f;
	float y_posBlockG2 = (float)IwGxGetScreenHeight() * 0.8f;
	for (int i = 0; i < 51; i++)
	{
		BlockG2[i] = new CSprite();
		BlockG2[i]->SetImage(g_pResources->getLevelBlock001G2());
		BlockG2[i]->m_X = (float)IwGxGetScreenWidth() * 10;
		BlockG2[i]->m_Y = (float)IwGxGetScreenHeight() * 10;
		BlockG2[i]->m_W = BlockG2[i]->GetImage()->GetWidth();
		BlockG2[i]->m_H = BlockG2[i]->GetImage()->GetHeight();
		BlockG2[i]->m_AnchorX = 0.5f;
		BlockG2[i]->m_AnchorY = 0.5f;
		BlockG2[i]->m_ScaleX = 1.0f;
		BlockG2[i]->m_ScaleY = 1.0f;
		AddChild(BlockG2[i]);
	}

	//height for the obstacles is assigned here for now/////////////////////////////////////////////////////////////////////////
	bigHeight = Block2[1]->m_H;
	bigWidth = Block2[1]->m_W;
}

void Game::Init()
{
	Scene::Init();

	currentRoundScore = 0;

	// Create Score Image
	float y_posScoreImage = (float)IwGxGetScreenHeight() * 0.1f;
	ScoreImage = new CSprite();
	ScoreImage->SetImage(g_pResources->getScoreImage());
	ScoreImage->m_X = IwGxGetScreenWidth() / 6;
	ScoreImage->m_Y = y_posScoreImage;
	ScoreImage->m_W = ScoreImage->GetImage()->GetWidth();
	ScoreImage->m_H = ScoreImage->GetImage()->GetHeight();
	ScoreImage->m_AnchorX = 0.5f;
	ScoreImage->m_AnchorY = 0.5f;
	ScoreImage->m_ScaleX = 0.75f;
	ScoreImage->m_ScaleY = 0.75f;
	AddChild(ScoreImage);

	// Create Distance Image
	float x_posDistanceImage = (float)IwGxGetScreenWidth() * 0.8f;
	float y_posDistanceImage = (float)IwGxGetScreenHeight() * 0.1f;
	DistanceImage = new CSprite();
	DistanceImage->SetImage(g_pResources->getDistanceImage());
	DistanceImage->m_X = x_posDistanceImage;
	DistanceImage->m_Y = y_posDistanceImage;
	DistanceImage->m_W = DistanceImage->GetImage()->GetWidth();
	DistanceImage->m_H = DistanceImage->GetImage()->GetHeight();
	DistanceImage->m_AnchorX = 0.5f;
	DistanceImage->m_AnchorY = 0.5f;
	DistanceImage->m_ScaleX = 0.75f;
	DistanceImage->m_ScaleY = 0.75f;
	AddChild(DistanceImage);

	// Initialise UI
	initUI();
	initLevel();
}

void Game::loopDrawImage(int draw)
{
	if (draw < 0)
	{
		for (int c = 0; c > draw; c--)
		{
			GameSquare->m_Y -= 1;
			//Iw2DDrawImage(image, image_position);
		}
	}
	if (draw >= 0)
	{
		for (int c = 0; c < draw; c++)
		{
			if (GameSquare->m_Y <= (float)IwGxGetScreenHeight() - ((float)IwGxGetScreenHeight() / 3))
			{
				GameSquare->m_Y += 1;
				//jumped = false;
			}
			//Iw2DDrawImage(image, image_position);
		}
	}
}
void Game::gravityDraw(int draw)
{
	if (draw < 0)
	{
		for (int c = 0; c > draw; c--)
		{
			if (GameSquare->m_Y >= (float)IwGxGetScreenHeight() - ((float)IwGxGetScreenHeight() / 1.2))
			{
				GameSquare->m_Y -= 1;
			}
			//Iw2DDrawImage(image, image_position);
		}
	}
	if (draw >= 0)
	{
		for (int c = 0; c < draw; c++)
		{
			if (GameSquare->m_Y <= (float)IwGxGetScreenHeight() - ((float)IwGxGetScreenHeight() / 3))
			{
				GameSquare->m_Y += 1;
			}
			//Iw2DDrawImage(image, image_position);
		}
	}
}

void Game::Yplaying()
{
	Playing = true;
	g_pInput->Reset();
	//return true;
}

void Game::Nplaying()
{
	Playing = false;
	g_pInput->Reset();
	//return true;
}

void Game::scrollJetpackMap(int draw)
{
	if (draw < 0)
	{
		for (int c = 0; c > draw; c--)
		{
			for (int i = 0; i < 50; i++)
			{
				//Block02[2]->m_X -= 1;
				//Block02[3]->m_X -= 1;
				//Block02[27]->m_X -= 1;
				//Block02[26]->m_X -= 1;
				Block2[i]->m_X -= 1;
				Coin1[i]->m_X -= 1;
				Gate1[i]->m_X -= 1;
				//Iw2DDrawImage(image, image_position);
			}
		}
	}
	if (draw >= 0)
	{
		for (int c = 0; c < draw; c++)
		{
			for (int i = 0; i < 50; i++)
			{
				//Block02[2]->m_X -= 1;
				//Block02[3]->m_X -= 1;
				//Block02[27]->m_X -= 1;
				//Block02[26]->m_X -= 1;
				Block2[i]->m_X -= 1;
				Coin1[i]->m_X -= 1;
				Gate1[i]->m_X -= 1;
			}
			//jumped = false;
			//Iw2DDrawImage(image, image_position);
		}
	}
}
void Game::smallShapeCollision(int ii)
{
	//This code sorts the collision out between the player and the small obstacle using a box shaped collision
	if (GameSquare->m_X - (GameSquare->m_W / 1.1f) <= Block2[ii]->m_X
		&& GameSquare->m_X >= Block2[ii]->m_X - (bigWidth / 2.5f)
		&& GameSquare->m_Y - (GameSquare->m_H / 4) <= Block2[ii]->m_Y
		&& GameSquare->m_Y >= Block2[ii]->m_Y - (bigHeight))
	{
		gameoverGame();
	}
}
void Game::bigShapeCollision(int jj)
{
	//This code sorts the collision out between the player and the big obstacle using a box shaped collision
	if (GameSquare->m_X - (GameSquare->m_W / 2) <= Block2[jj]->m_X + (Block2[jj]->m_W / 2)
		&& GameSquare->m_X + (GameSquare->m_W / 2) >= Block2[jj]->m_X - (bigWidth / 2)
		&& GameSquare->m_Y - (GameSquare->m_H) <= Block2[jj]->m_Y 
		&& GameSquare->m_Y >= Block2[jj]->m_Y - (bigHeight))
	{
		gameoverGame();
	}
	if (GameSquare->m_X - (GameSquare->m_W / 2) <= Gate1[jj]->m_X + (Gate1[jj]->m_W / 2)
		&& GameSquare->m_X + (GameSquare->m_W / 2) >= Gate1[jj]->m_X - (bigWidth / 2)
		&& GameSquare->m_Y - (GameSquare->m_H) <= Gate1[jj]->m_Y
		&& GameSquare->m_Y >= Gate1[jj]->m_Y - (bigHeight))
	{
		laneLVL1();
		//laneLEVEL01();
		addToRoundScore(1000, jj);
	}
	if (GameSquare->m_X - (GameSquare->m_W / 2) <= Coin1[jj]->m_X + (Coin1[jj]->m_W / 2)
		&& GameSquare->m_X + (GameSquare->m_W / 2) >= Coin1[jj]->m_X - (bigWidth / 2)
		&& GameSquare->m_Y - (GameSquare->m_H) <= Coin1[jj]->m_Y
		&& GameSquare->m_Y >= Coin1[jj]->m_Y - (bigHeight))
	{
		addToRoundScore(10,jj);
	}
}

// ############### BELOW IS THE ATTEMPT FOR SCORE POINTS ###############
/*void Game::bigShapeScore(int jj)
{
	//This code sorts the collision out between the player and the big obstacle using a box shaped collision
	if (GameSquare->m_X - (GameSquare->m_W / 2) <= Coin1[jj]->m_X + (Coin1[jj]->m_W / 2)
		&& GameSquare->m_X + (GameSquare->m_W / 2) >= Coin1[jj]->m_X - (bigWidth / 2)
		&& GameSquare->m_Y - (GameSquare->m_H) <= Coin1[jj]->m_Y
		&& GameSquare->m_Y >= Coin1[jj]->m_Y - (bigHeight))
	{
		addToRoundScore();
	}
}*/
// ###################################################################

//below is the area where the levels will be sorted, all that needs to be done is the shapes in the array will be put in at various coordinates and the position wil be saved in level functions
void Game::gravityMap()
{
	Block2[27]->m_Y = (float)IwGxGetScreenWidth() / 2.5f;;
	Block2[27]->m_X = (float)IwGxGetScreenHeight() * 2.0f;
	Block2[26]->m_Y = (float)IwGxGetScreenHeight() / 5;
	Block2[26]->m_X = (float)IwGxGetScreenHeight() * 2.0f;
	Block1->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	Block2[1]->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	Block3->m_Y = (float)IwGxGetScreenHeight() * 0.8f;


}
void Game::jumpMap()
{

	Block2[27]->m_Y = (float)IwGxGetScreenWidth() / 2.5f;;
	Block2[27]->m_X = (float)IwGxGetScreenHeight() * 2.0f;

}
void Game::jetPackMap()
{
	Block2[2]->m_Y = (float)IwGxGetScreenHeight() / 5;
	Block2[2]->m_X = (float)IwGxGetScreenHeight() * 2.0f;


}
void Game::laneMap()
{
	Block1->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	Block2[1]->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	Block3->m_Y = (float)IwGxGetScreenHeight() * 0.8f;

	/*Block2[26]->m_Y = (float)IwGxGetScreenWidth() / 4.5f;;
	Block2[26]->m_X = (float)IwGxGetScreenHeight() * 2.0f;*/

	laneLVL1();
	//laneLEVEL01();
}
void Game::laneLVL1()
{
	float a = 0;
	float top = 6.0f;
	float topmid = 3.0f;
	float middle = 2.2f;
	float midbot = 1.7f;
	float bottom = 1.4f;

	// Experiment: The Coin blocks that will help increment the score when shape collides with them
	Coin1[0]->m_X = (float)IwGxGetScreenWidth() * ((1.0f / 5.0f) + 1.0f);
	Coin1[0]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Coin1[1]->m_X = (float)IwGxGetScreenWidth() * ((1.0f / 5.0f) + 1.0f);
	Coin1[1]->m_Y = (float)IwGxGetScreenHeight() / top;
	Coin1[2]->m_X = (float)IwGxGetScreenWidth() * ((3.0f / 5.0f) + 1.0f);
	Coin1[2]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Coin1[3]->m_X = (float)IwGxGetScreenWidth() * ((4.0f / 5.0f) + 1.0f);
	Coin1[3]->m_Y = (float)IwGxGetScreenHeight() / top;
	Coin1[4]->m_X = (float)IwGxGetScreenWidth() * ((5.0f / 5.0f) + 1.0f);
	Coin1[4]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Coin1[5]->m_X = (float)IwGxGetScreenWidth() * ((6.0f / 5.0f) + 1.0f);
	Coin1[5]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Coin1[6]->m_X = (float)IwGxGetScreenWidth() * ((7.0f / 5.0f) + 1.0f);
	Coin1[6]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Coin1[7]->m_X = (float)IwGxGetScreenWidth() * ((8.0f / 5.0f) + 1.0f);
	Coin1[7]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Coin1[8]->m_X = (float)IwGxGetScreenWidth() * ((9.0f / 5.0f) + 1.0f);
	Coin1[8]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Coin1[9]->m_X = (float)IwGxGetScreenWidth() * ((9.0f / 5.0f) + 1.0f);
	Coin1[9]->m_Y = (float)IwGxGetScreenHeight() / top;
	Coin1[10]->m_X = (float)IwGxGetScreenWidth() * ((10.0f / 5.0f) + 1.0f);
	Coin1[10]->m_Y = (float)IwGxGetScreenHeight() / middle;

	// ### The Collision Blocks: Section 11-20 ###
	// the x values for the map items
	Block2[11]->m_X = (float)IwGxGetScreenWidth() * ((11.0f / 5.0f) + 1.0f);
	Block2[12]->m_X = (float)IwGxGetScreenWidth() * ((11.0f / 5.0f) + 1.0f);
	Block2[13]->m_X = (float)IwGxGetScreenWidth() * ((12.0f / 5.0f) + 1.0f);
	Block2[14]->m_X = (float)IwGxGetScreenWidth() * ((12.0f / 5.0f) + 1.0f);
	Block2[15]->m_X = (float)IwGxGetScreenWidth() * ((13.0f / 5.0f) + 1.0f);
	Block2[16]->m_X = (float)IwGxGetScreenWidth() * ((14.0f / 5.0f) + 1.0f);
	Block2[17]->m_X = (float)IwGxGetScreenWidth() * ((14.0f / 5.0f) + 1.0f);
	Block2[18]->m_X = (float)IwGxGetScreenWidth() * ((15.0f / 5.0f) + 1.0f);
	Block2[19]->m_X = (float)IwGxGetScreenWidth() * ((16.0f / 5.0f) + 1.0f);
	Block2[20]->m_X = (float)IwGxGetScreenWidth() * ((16.0f / 5.0f) + 1.0f);
	
	// the y values for the map items
	Block2[11]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[12]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[13]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[14]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[15]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[16]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[17]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[18]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[19]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[20]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	
	// ### The Collision Blocks: Section 21-30 ###
	// the x values for the map items
	Block2[21]->m_X = (float)IwGxGetScreenWidth() * ((17.0f / 5.0f) + 1.0f);
	Block2[22]->m_X = (float)IwGxGetScreenWidth() * ((18.0f / 5.0f) + 1.0f);
	Block2[23]->m_X = (float)IwGxGetScreenWidth() * ((19.0f / 5.0f) + 1.0f);
	Block2[24]->m_X = (float)IwGxGetScreenWidth() * ((19.0f / 5.0f) + 1.0f);
	Block2[25]->m_X = (float)IwGxGetScreenWidth() * ((20.0f / 5.0f) + 1.0f);
	Block2[26]->m_X = (float)IwGxGetScreenWidth() * ((21.0f / 5.0f) + 1.0f);
	Block2[27]->m_X = (float)IwGxGetScreenWidth() * ((22.0f / 5.0f) + 1.0f);
	Block2[28]->m_X = (float)IwGxGetScreenWidth() * ((23.0f / 5.0f) + 1.0f);
	Block2[29]->m_X = (float)IwGxGetScreenWidth() * ((24.0f / 5.0f) + 1.0f);
	Block2[30]->m_X = (float)IwGxGetScreenWidth() * ((24.0f / 5.0f) + 1.0f);
	
	// the y values for the map items
	Block2[21]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[22]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[23]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[24]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[25]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[26]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[27]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[28]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[29]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[30]->m_Y = (float)IwGxGetScreenHeight() / middle;
	
	// ### The Collision Blocks: Section 31-41 ###
	// the x values for the map items
	Block2[31]->m_X = (float)IwGxGetScreenWidth() * ((25.0f / 5.0f) + 1.0f);
	Block2[32]->m_X = (float)IwGxGetScreenWidth() * ((26.0f / 5.0f) + 1.0f);
	Block2[33]->m_X = (float)IwGxGetScreenWidth() * ((26.0f / 5.0f) + 1.0f);
	Block2[34]->m_X = (float)IwGxGetScreenWidth() * ((27.0f / 5.0f) + 1.0f);
	Block2[35]->m_X = (float)IwGxGetScreenWidth() * ((28.0f / 5.0f) + 1.0f);
	Block2[36]->m_X = (float)IwGxGetScreenWidth() * ((29.0f / 5.0f) + 1.0f);
	Block2[37]->m_X = (float)IwGxGetScreenWidth() * ((30.0f / 5.0f) + 1.0f);
	Block2[38]->m_X = (float)IwGxGetScreenWidth() * ((31.0f / 5.0f) + 1.0f);
	Block2[39]->m_X = (float)IwGxGetScreenWidth() * ((31.0f / 5.0f) + 1.0f);
	Block2[40]->m_X = (float)IwGxGetScreenWidth() * ((32.0f / 5.0f) + 1.0f);
	Block2[41]->m_X = (float)IwGxGetScreenWidth() * ((32.0f / 5.0f) + 1.0f);
	
	// the y values for the map items
	Block2[31]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[32]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[33]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[34]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[35]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[36]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[37]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[38]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[39]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[40]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[41]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	
	// ### The Collision Blocks: Section 42-49 ###
	// the x values for the map items
	Block2[42]->m_X = (float)IwGxGetScreenWidth() * ((33.0f / 5.0f) + 1.0f);
	Block2[43]->m_X = (float)IwGxGetScreenWidth() * ((34.0f / 5.0f) + 1.0f);
	Block2[44]->m_X = (float)IwGxGetScreenWidth() * ((35.0f / 5.0f) + 1.0f);
	Block2[45]->m_X = (float)IwGxGetScreenWidth() * ((37.0f / 5.0f) + 1.0f);
	Block2[46]->m_X = (float)IwGxGetScreenWidth() * ((37.0f / 5.0f) + 1.0f);
	Block2[47]->m_X = (float)IwGxGetScreenWidth() * ((39.0f / 5.0f) + 1.0f);
	Block2[48]->m_X = (float)IwGxGetScreenWidth() * ((39.0f / 5.0f) + 1.0f);
	Block2[49]->m_X = (float)IwGxGetScreenWidth() * ((40.0f / 5.0f) + 1.0f);
	
	// the y values for the map items
	Block2[42]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[43]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[44]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[45]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[46]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Block2[47]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	Block2[48]->m_Y = (float)IwGxGetScreenHeight() / top;
	Block2[49]->m_Y = (float)IwGxGetScreenHeight() / top;
	
	// ### The Collision Gate ###
	// the x values for the map items
	Gate1[30]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[31]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[32]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[33]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[34]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);

	// the y values for the map items
	Gate1[30]->m_Y = (float)IwGxGetScreenHeight() / top;
	Gate1[31]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	Gate1[32]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Gate1[33]->m_Y = (float)IwGxGetScreenHeight() / midbot;
	Gate1[34]->m_Y = (float)IwGxGetScreenHeight() / bottom;
}
void Game::resetGame()
{
	initRound();
	laneMap();
	powerup = 1;
}
// ############################# PROPOSED DESIGN FOR LEVEL 01 #############################
void Game::laneLEVEL01()
{
	float a = 0;
	float top = 6.0f;
	float topmid = 3.0f;
	float middle = 2.2f;
	float midbot = 1.7f;
	float bottom = 1.4f;
	
	/*
	For reference the following Blocks are used:
	{ Block01 								   }
	{ BlockA1, BlockA2, BlockA3, BlockA4	   }
	{ BlockB1, BlockB2						   }
	{ BlockC1, BlockC2, BlockC3, BlockC4	   }
	{ BlockD1, BlockD2						   }
	{ BlockE								   }
	{ BlockG2								   }
	*/

	// ###========### Collision Blocks: Section 00-10 ###========###
	// X Co-ordinates
	BlockC2[0]->m_X = (float)IwGxGetScreenWidth() * ((1.0f / 5.0f) + 1.0f);		// Section 00
	BlockB1[0]->m_X = (float)IwGxGetScreenWidth() * ((1.0f / 5.0f) + 1.0f);	
	BlockB1[1]->m_X = (float)IwGxGetScreenWidth() * ((1.0f / 5.0f) + 1.0f);		// Section 01
	Block01[0]->m_X = (float)IwGxGetScreenWidth() * ((3.0f / 5.0f) + 1.0f);		// Section 02
	BlockC2[1]->m_X = (float)IwGxGetScreenWidth() * ((4.0f / 5.0f) + 1.0f);		// Section 03
	BlockA1[0]->m_X = (float)IwGxGetScreenWidth() * ((5.0f / 5.0f) + 1.0f);		// Section 04
	BlockD1[0]->m_X = (float)IwGxGetScreenWidth() * ((5.5f / 5.0f) + 1.0f);
	BlockA2[0]->m_X = (float)IwGxGetScreenWidth() * ((6.0f / 5.0f) + 1.0f);		// Section 05
	BlockC3[0]->m_X = (float)IwGxGetScreenWidth() * ((7.0f / 5.0f) + 1.0f);		// Section 06
	BlockB2[0]->m_X = (float)IwGxGetScreenWidth() * ((7.5f / 5.0f) + 1.0f);
	BlockB2[1]->m_X = (float)IwGxGetScreenWidth() * ((8.0f / 5.0f) + 1.0f);		// Section 07
	BlockB2[2]->m_X = (float)IwGxGetScreenWidth() * ((8.5f / 5.0f) + 1.0f);
	BlockC2[2]->m_X = (float)IwGxGetScreenWidth() * ((9.0f / 5.0f) + 1.0f);
	BlockE[0]->m_X = (float)IwGxGetScreenWidth() * ((9.0f / 5.0f) + 1.0f);		// Section 08
	BlockB1[2]->m_X = (float)IwGxGetScreenWidth() * ((9.0f / 5.0f) + 1.0f);
	BlockB1[3]->m_X = (float)IwGxGetScreenWidth() * ((9.0f / 5.0f) + 1.0f);		// Section 09
	BlockB2[3]->m_X = (float)IwGxGetScreenWidth() * ((9.5f / 5.0f) + 1.0f);
	BlockC4[0]->m_X = (float)IwGxGetScreenWidth() * ((10.0f / 5.0f) + 1.0f);	// Section 10
	
	// Y Co-ordinates
	BlockC2[0]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 00
	BlockB1[0]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	BlockB1[1]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 01
	Block01[0]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 02
	BlockC2[1]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 03
	BlockA1[0]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 04
	BlockD1[0]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	BlockA2[0]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 05
	BlockC3[0]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 06
	BlockB2[0]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockB2[1]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 07
	BlockB2[2]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockC2[2]->m_Y = (float)IwGxGetScreenHeight() / midbot;
	BlockE[0]->m_Y = (float)IwGxGetScreenHeight() / middle;		// Section 08
	BlockB1[2]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	BlockB1[3]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 09
	BlockB2[3]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockC4[0]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 10
	
	// ###========### Collision Blocks: Section 11-20 ###========###
	// X Co-ordinates
	BlockA3[0]->m_X = (float)IwGxGetScreenWidth() * ((11.0f / 5.0f) + 1.0f);	// Section 11
	BlockA1[1]->m_X = (float)IwGxGetScreenWidth() * ((11.0f / 5.0f) + 1.0f);	// Section 12
	BlockD2[0]->m_X = (float)IwGxGetScreenWidth() * ((11.5f / 5.0f) + 1.0f);
	BlockD1[1]->m_X = (float)IwGxGetScreenWidth() * ((11.5f / 5.0f) + 1.0f);
	BlockD2[1]->m_X = (float)IwGxGetScreenWidth() * ((12.0f / 5.0f) + 1.0f);	// Section 13
	BlockA2[1]->m_X = (float)IwGxGetScreenWidth() * ((12.0f / 5.0f) + 1.0f);	// Section 14
	BlockD2[2]->m_X = (float)IwGxGetScreenWidth() * ((12.5f / 5.0f) + 1.0f);
	BlockD2[3]->m_X = (float)IwGxGetScreenWidth() * ((13.0f / 5.0f) + 1.0f);	// Section 15
	BlockD2[4]->m_X = (float)IwGxGetScreenWidth() * ((13.5f / 5.0f) + 1.0f);
	BlockC3[1]->m_X = (float)IwGxGetScreenWidth() * ((13.5f / 5.0f) + 1.0f);
	BlockC2[3]->m_X = (float)IwGxGetScreenWidth() * ((14.0f / 5.0f) + 1.0f);
	BlockE[1]->m_X = (float)IwGxGetScreenWidth() * ((14.0f / 5.0f) + 1.0f);		// Section 16
	BlockB1[4]->m_X = (float)IwGxGetScreenWidth() * ((14.0f / 5.0f) + 1.0f);
	BlockG2[0]->m_X = (float)IwGxGetScreenWidth() * ((14.0f / 5.0f) + 1.0f);	// Section 17
	BlockA4[0]->m_X = (float)IwGxGetScreenWidth() * ((14.5f / 5.0f) + 1.0f);
	BlockB2[4]->m_X = (float)IwGxGetScreenWidth() * ((14.5f / 5.0f) + 1.0f);
	BlockB2[5]->m_X = (float)IwGxGetScreenWidth() * ((15.0f / 5.0f) + 1.0f);	// Section 18
	BlockB2[6]->m_X = (float)IwGxGetScreenWidth() * ((15.5f / 5.0f) + 1.0f);
	BlockC1[0]->m_X = (float)IwGxGetScreenWidth() * ((16.0f / 5.0f) + 1.0f);
	BlockE[2]->m_X = (float)IwGxGetScreenWidth() * ((16.0f / 5.0f) + 1.0f);		// Section 19
	BlockB1[5]->m_X = (float)IwGxGetScreenWidth() * ((16.0f / 5.0f) + 1.0f);
	BlockB1[6]->m_X = (float)IwGxGetScreenWidth() * ((16.0f / 5.0f) + 1.0f);	// Section 20
	BlockB2[7]->m_X = (float)IwGxGetScreenWidth() * ((16.5f / 5.0f) + 1.0f);
	
	// Y Co-ordinates
	BlockA3[0]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 11
	BlockA1[1]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 12
	BlockD2[0]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockD1[1]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	BlockD2[1]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 13
	BlockA2[1]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 14
	BlockD2[2]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockD2[3]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 15
	BlockD2[4]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockC3[1]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockC2[3]->m_Y = (float)IwGxGetScreenHeight() / midbot;
	BlockE[1]->m_Y = (float)IwGxGetScreenHeight() / middle;		// Section 16
	BlockB1[4]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	BlockG2[0]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 17
	BlockA4[0]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockB2[4]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockB2[5]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 18
	BlockB2[6]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockC1[0]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	BlockE[2]->m_Y = (float)IwGxGetScreenHeight() / middle;		// Section 19
	BlockB1[5]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	BlockB1[6]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 20
	BlockB2[7]->m_Y = (float)IwGxGetScreenHeight() / middle;
	
	// ###========### Collision Blocks: Section 21-30 ###========###
	// X Co-ordinates
	BlockC4[1]->m_X = (float)IwGxGetScreenWidth() * ((17.0f / 5.0f) + 1.0f);	// Section 21
	BlockA3[1]->m_X = (float)IwGxGetScreenWidth() * ((18.0f / 5.0f) + 1.0f);	// Section 22
	BlockD2[5]->m_X = (float)IwGxGetScreenWidth() * ((18.5f / 5.0f) + 1.0f);
	BlockA4[1]->m_X = (float)IwGxGetScreenWidth() * ((19.0f / 5.0f) + 1.0f);	// Section 23
	BlockA1[2]->m_X = (float)IwGxGetScreenWidth() * ((19.0f / 5.0f) + 1.0f);	// Section 24
	BlockD1[2]->m_X = (float)IwGxGetScreenWidth() * ((19.5f / 5.0f) + 1.0f);
	BlockD1[3]->m_X = (float)IwGxGetScreenWidth() * ((20.0f / 5.0f) + 1.0f);	// Section 25
	BlockD1[4]->m_X = (float)IwGxGetScreenWidth() * ((20.5f / 5.0f) + 1.0f);
	BlockA2[2]->m_X = (float)IwGxGetScreenWidth() * ((21.0f / 5.0f) + 1.0f);	// Section 26
	Block01[1]->m_X = (float)IwGxGetScreenWidth() * ((22.0f / 5.0f) + 1.0f);	// Section 27
	BlockA3[2]->m_X = (float)IwGxGetScreenWidth() * ((23.0f / 5.0f) + 1.0f);	// Section 28
	BlockD2[6]->m_X = (float)IwGxGetScreenWidth() * ((23.5f / 5.0f) + 1.0f);
	BlockA4[2]->m_X = (float)IwGxGetScreenWidth() * ((24.0f / 5.0f) + 1.0f);	// Section 29
	BlockC1[1]->m_X = (float)IwGxGetScreenWidth() * ((24.0f / 5.0f) + 1.0f);	// Section 30

	// Y Co-ordinates
	BlockC4[1]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 21
	BlockA3[1]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 22
	BlockD2[5]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockA4[1]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 23
	BlockA1[2]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 24
	BlockD1[2]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	BlockD1[3]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 25
	BlockD1[4]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	BlockA2[2]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 26
	Block01[1]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 27
	BlockA3[2]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 28
	BlockD2[6]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockA4[2]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 29
	BlockC1[1]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 30

	// ###========### Collision Blocks: Section 31-41 ###========###
	// X Co-ordinates
	BlockC3[2]->m_X = (float)IwGxGetScreenWidth() * ((25.0f / 5.0f) + 1.0f);	// Section 31
	BlockB2[8]->m_X = (float)IwGxGetScreenWidth() * ((25.5f / 5.0f) + 1.0f);
	BlockC1[2]->m_X = (float)IwGxGetScreenWidth() * ((26.0f / 5.0f) + 1.0f);
	BlockE[2]->m_X = (float)IwGxGetScreenWidth() * ((26.0f / 5.0f) + 1.0f);		// Section 32
	BlockB1[7]->m_X = (float)IwGxGetScreenWidth() * ((26.0f / 5.0f) + 1.0f);
	BlockB1[8]->m_X = (float)IwGxGetScreenWidth() * ((26.0f / 5.0f) + 1.0f);	// Section 33
	BlockB2[9]->m_X = (float)IwGxGetScreenWidth() * ((26.5f / 5.0f) + 1.0f);
	BlockB2[10]->m_X = (float)IwGxGetScreenWidth() * ((27.0f / 5.0f) + 1.0f);	// Section 34
	BlockB2[11]->m_X = (float)IwGxGetScreenWidth() * ((27.5f / 5.0f) + 1.0f);
	BlockB2[12]->m_X = (float)IwGxGetScreenWidth() * ((28.0f / 5.0f) + 1.0f);	// Section 35
	BlockB2[13]->m_X = (float)IwGxGetScreenWidth() * ((28.5f / 5.0f) + 1.0f);
	BlockC4[1]->m_X = (float)IwGxGetScreenWidth() * ((29.0f / 5.0f) + 1.0f);	// Section 36
	BlockA3[3]->m_X = (float)IwGxGetScreenWidth() * ((30.0f / 5.0f) + 1.0f);	// Section 37
	BlockD2[7]->m_X = (float)IwGxGetScreenWidth() * ((30.5f / 5.0f) + 1.0f);
	BlockD2[8]->m_X = (float)IwGxGetScreenWidth() * ((31.0f / 5.0f) + 1.0f);	// Section 38
	BlockA1[3]->m_X = (float)IwGxGetScreenWidth() * ((31.0f / 5.0f) + 1.0f);	// Section 39
	BlockD2[9]->m_X = (float)IwGxGetScreenWidth() * ((31.5f / 5.0f) + 1.0f);
	BlockD1[5]->m_X = (float)IwGxGetScreenWidth() * ((31.5f / 5.0f) + 1.0f);
	BlockD2[10]->m_X = (float)IwGxGetScreenWidth() * ((32.0f / 5.0f) + 1.0f);	// Section 40
	BlockA2[3]->m_X = (float)IwGxGetScreenWidth() * ((32.0f / 5.0f) + 1.0f);	// Section 41
	BlockD2[11]->m_X = (float)IwGxGetScreenWidth() * ((32.5f / 5.0f) + 1.0f);
	
	// the y values for the map items
	BlockC3[2]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 31
	BlockB2[8]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockC1[2]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	BlockE[2]->m_Y = (float)IwGxGetScreenHeight() / middle;		// Section 32
	BlockB1[7]->m_Y = (float)IwGxGetScreenHeight() / midbot;
	BlockB1[8]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 33
	BlockB2[9]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockB2[10]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 34
	BlockB2[11]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockB2[12]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 35
	BlockB2[13]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockC4[1]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 36
	BlockA3[3]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 37
	BlockD2[7]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockD2[8]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 38
	BlockA1[3]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 39
	BlockD2[9]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockD1[5]->m_Y = (float)IwGxGetScreenHeight() / bottom;
	BlockD2[10]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 40
	BlockA2[3]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 41
	BlockD2[11]->m_Y = (float)IwGxGetScreenHeight() / top;
	
	// ###========### Collision Blocks: Section 42-49 ###========###
	// X Co-ordinates
	BlockA4[3]->m_X = (float)IwGxGetScreenWidth() * ((33.0f / 5.0f) + 1.0f);	// Section 42
	BlockC3[3]->m_X = (float)IwGxGetScreenWidth() * ((34.0f / 5.0f) + 1.0f);	// Section 43
	BlockB2[14]->m_X = (float)IwGxGetScreenWidth() * ((34.5f / 5.0f) + 1.0f);
	BlockC4[2]->m_X = (float)IwGxGetScreenWidth() * ((35.0f / 5.0f) + 1.0f);	// Section 44
	BlockB1[9]->m_X = (float)IwGxGetScreenWidth() * ((37.0f / 5.0f) + 1.0f);	// Section 45
	BlockB1[10]->m_X = (float)IwGxGetScreenWidth() * ((37.0f / 5.0f) + 1.0f);
	BlockC2[4]->m_X = (float)IwGxGetScreenWidth() * ((37.0f / 5.0f) + 1.0f);	// Section 46
	BlockA3[4]->m_X = (float)IwGxGetScreenWidth() * ((39.0f / 5.0f) + 1.0f);	// Section 47
	BlockC1[3]->m_X = (float)IwGxGetScreenWidth() * ((39.0f / 5.0f) + 1.0f);	// Section 48
	BlockD2[12]->m_X = (float)IwGxGetScreenWidth() * ((39.5f / 5.0f) + 1.0f);
	BlockA4[4]->m_X = (float)IwGxGetScreenWidth() * ((40.0f / 5.0f) + 1.0f);	// Section 49
	
	// Y Co-ordinates
	BlockA4[3]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 42
	BlockC3[3]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 43
	BlockB2[14]->m_Y = (float)IwGxGetScreenHeight() / middle;
	BlockC4[2]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 44
	BlockB1[9]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 45
	BlockB1[10]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	BlockC2[4]->m_Y = (float)IwGxGetScreenHeight() / middle;	// Section 46
	BlockA3[4]->m_Y = (float)IwGxGetScreenHeight() / bottom;	// Section 47
	BlockC1[3]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 48
	BlockD2[12]->m_Y = (float)IwGxGetScreenHeight() / top;
	BlockA4[4]->m_Y = (float)IwGxGetScreenHeight() / top;		// Section 49
	
	// ###========### Collision Gate ###========###
	// X Co-ordinates
	Gate1[0]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[1]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[2]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[3]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);
	Gate1[4]->m_X = (float)IwGxGetScreenWidth() * ((42.0f / 5.0f) + 1.0f);

	// Y Co-ordinates
	Gate1[0]->m_Y = (float)IwGxGetScreenHeight() / top;
	Gate1[1]->m_Y = (float)IwGxGetScreenHeight() / topmid;
	Gate1[2]->m_Y = (float)IwGxGetScreenHeight() / middle;
	Gate1[3]->m_Y = (float)IwGxGetScreenHeight() / midbot;
	Gate1[4]->m_Y = (float)IwGxGetScreenHeight() / bottom;
}