#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
private:

	static const int MAX_VERTS = 4;

	GameEntity* mVerts[MAX_VERTS];

public:

	BoxCollider(Vector2 size);
	~BoxCollider();

private:

	void AddVertex(int index, Vector2 pos);

};