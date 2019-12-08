#include "Monster.h"

Monster::Monster()
{
	//mTexture = new AnimatedTexture("collider.png", 0.0f, 0.0f, 32, 32, 1, 1.0f, AnimatedTexture::horizontal);
	mTexture = new AnimatedTexture("monster.png", 0.0f, 0.0f, 64, 64, 4, 0.25f, AnimatedTexture::horizontal);
	mTexture->Parent(this);
}

Monster::~Monster()
{
	delete mTexture;
	mTexture = NULL;
}

void Monster::Move()
{
}

void Monster::Update()
{
	mTexture->Update();
}

void Monster::Render()
{
	mTexture->Render();
}
