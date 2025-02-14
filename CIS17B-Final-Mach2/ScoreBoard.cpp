#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() : ScoreBoard({ 255,255,255 })
{

}

ScoreBoard::ScoreBoard(SDL_Color color)
{
	mColor = color;
	Score(0);
}

ScoreBoard::~ScoreBoard()
{
	ClearBoard();
}

void ScoreBoard::ClearBoard()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}

void ScoreBoard::Score(int score)
{
	ClearBoard();

	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", "forgotmybazookaathome.ttf", 32, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f*i, 0.0f));
		}
	}

	else
	{
		std::string str = std::to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; i++)
		{
			mScore.push_back(new Texture(str.substr(i, 1), "forgotmybazookaathome.ttf", 32, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f*(lastIndex - i), 0.0f));
		}
	}
}

void ScoreBoard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}