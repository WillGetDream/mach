#pragma once
#include "AnimatedTexture.h"

using namespace QuickSDL;

class Monster:public GameEntity
{
public:

	AnimatedTexture* mTexture;
	
public:

	Monster();
	~Monster();

	// Lerp between enemy's position and player's position
	void Move();

	void Update();
	void Render();
};