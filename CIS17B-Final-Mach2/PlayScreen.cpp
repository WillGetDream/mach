#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mHUD = new HUD();

	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mBeginLabel0 = new Texture(" PREPARE TO ", "forgotmybazookaathome.ttf", 48, { 255,255,255 });
	mBeginLabel1 = new Texture("INVESTIGATE!", "forgotmybazookaathome.ttf", 48, { 255,255,255 });
	mBeginLabel0->Parent(this);
	mBeginLabel1->Parent(this);
	mBeginLabel0->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f - 48));
	mBeginLabel1->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f + 48));

	//==============
	mLevelLabel = new Texture("LEVEL", "forgotmybazookaathome.ttf", 24, { 64,64,255 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f - 13, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevelNumber = new ScoreBoard({ 64, 64, 255 });
	mLevelNumber->Score(mCurrentLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f + 123, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	//==============

	mPlayer = NULL;

	// Map stuff
	mTileSetPath = "tileset2.png";
	CreateMaps();

	for (Map* m : mMaps)
		m->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - m->mSizeX * m->TILE_SIZE) * 0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - m->mSizeY * m->TILE_SIZE) * 0.5f + 32.0f));

	for (Map* fx : mFxMaps)
		fx->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH - fx->mSizeX * fx->TILE_SIZE) * 0.5f,
		(Graphics::Instance()->SCREEN_HEIGHT - fx->mSizeY * fx->TILE_SIZE) * 0.5f + 32.0f));
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;

	delete mHUD;
	mHUD = NULL;

	delete mBeginLabel0;
	mBeginLabel0 = NULL;
	delete mBeginLabel1;
	mBeginLabel1 = NULL;

	delete mPlayer;
	mPlayer = NULL;

	//==============
	delete mLevelLabel;
	mLevelLabel = NULL;
	delete mLevelNumber;
	mLevelNumber = NULL;
	//==============

	for (Map* m : mMaps)
	{
		delete m;
		m = NULL;
	}

	for (Map* m : mFxMaps)
	{
		delete m;
		m = NULL;
	}
}

void PlayScreen::StartNextLevel()
{
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	if (mCurrentLevel == 1)
		mAudio->PlayMusic("SMRPG_BarrelVocano_LH.wav", -1);
	if (mCurrentLevel > 0)
	{
		mMaps[mCurrentLevel - 1]->LoadMap();
		mFxMaps[mCurrentLevel - 1]->LoadMap();
		mPlayer->Pos(mStartPos[mCurrentLevel-1]);
		//mPlayer->Pos()->mStartPos[mCurrentLevel - 1];
	}
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mPlayer->Active(false);

	mCurrentLevel = 0;
	mHUD->SetCurrentScore(0);
	mGameStarted = false;
	mLevelStarted = false; // in case this is second go-around
	mAudio->PlayMusic("smrpg_battlestart_padded.wav", 0); //0: no loop, -1(default): infinite loop
}

void PlayScreen::CreateMaps()
{
	const std::string path = "Debug\\Assets\\";
	mMaps[0] = new Map(mTileSetPath, path + "map00.map", 15, 15);
	mFxMaps[0] = new Map(mTileSetPath, path + "mapFx00.map", 11, 11);
	mStartPos[0] = Vector2(474, 196);

	mMaps[1] = new Map(mTileSetPath, path + "map01.map", 21, 21);
	mFxMaps[1] = new Map(mTileSetPath, path + "mapFx01.map", 11, 11);
	mStartPos[1] = Vector2(379, 111);

	mMaps[2] = new Map(mTileSetPath, path + "map02.map", 31, 11);
	mFxMaps[2] = new Map(mTileSetPath, path + "mapFx02.map", 11, 11);
	mStartPos[2] = Vector2(216, 271);


	mMaps[3] = new Map(mTileSetPath, path + "map03.map", 31, 15);
	mFxMaps[3] = new Map(mTileSetPath, path + "mapFx03.map", 11, 11);
	mStartPos[3] = Vector2(219, 204);


	mMaps[4] = new Map(mTileSetPath, path + "map04.map", 21, 21);
	mFxMaps[4] = new Map(mTileSetPath, path + "mapFx04.map", 11, 11);
	mStartPos[4] = Vector2(378, 173);


	mMaps[5] = new Map(mTileSetPath, path + "map05.map", 39, 19);
	mFxMaps[5] = new Map(mTileSetPath, path + "mapFx05.map", 11, 11);
	mStartPos[5] = Vector2(153, 140);


	mMaps[6] = new Map(mTileSetPath, path + "map06.map", 31, 21);
	mFxMaps[6] = new Map(mTileSetPath, path + "mapFx06.map", 11, 11);
	mStartPos[6] = Vector2(218, 113);


	mMaps[7] = new Map(mTileSetPath, path + "map07.map", 39, 21);
	mFxMaps[7] = new Map(mTileSetPath, path + "mapFx07.map", 11, 11);
	mStartPos[7] = Vector2(87, 108);


	mMaps[8] = new Map(mTileSetPath, path + "map08.map", 39, 21);
	mFxMaps[8] = new Map(mTileSetPath, path + "mapFx08.map", 11, 11);
	mStartPos[8] = Vector2(155, 303);


	mMaps[9] = new Map(mTileSetPath, path + "map09.map", 39, 21);
	mFxMaps[9] = new Map(mTileSetPath, path + "mapFx09.map", 11, 11);
	mStartPos[9] = Vector2(1243, 108);

}

void PlayScreen::Update()
{
	std::cout << mPlayer->Pos() << std::endl;
	if (mGameStarted && mLevelStarted)
	{
		mPlayer->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_N))
		{
			mLevelStarted = false;
			mPlayer->Active(false);
			mPlayer->Visible(false);
		}
	}
	else if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
	else
	{
		// WARNING! This test will fail if it is testing "music" played with PlaySFX()
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
		}
	}
	//std::cout << "GameStarted: " << mGameStarted << std::endl;
	//std::cout << "LevelStarted: " << mLevelStarted << std::endl;
	//system("CLS");
}

void PlayScreen::Render()
{

	if (!mGameStarted)
	{
		mBeginLabel0->Render();
		mBeginLabel1->Render();
	}
	if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			if (mLevelStartTimer == 0)
			{
				mCurrentLevel++;
				mLevelNumber->Score(mCurrentLevel);
				mHUD->SetCurrentScore(mCurrentLevel);
			}
			if (mLevelStartTimer > 0.0f && mLevelStartTimer < mLevelStartDelay)
			{
				mLevelLabel->Render();
				mLevelNumber->Render();
			}
		}
		if (mLevelStarted)
		{
			if (mCurrentLevel > 0)
				mMaps[mCurrentLevel - 1]->Render();
			mPlayer->Active(true);
			mPlayer->Visible(true);
			mPlayer->Render();
			if (mCurrentLevel > 0)
				mFxMaps[mCurrentLevel - 1]->Render();
		}
		mHUD->Render();
	}
}