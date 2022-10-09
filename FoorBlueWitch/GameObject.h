#pragma once

#include <vector>
#include "Math.h"

extern std::vector<class GameObject*> gameObjectList;

class GameObject {
	class Renderer* render = nullptr;

public:
	Vector position;

	GameObject(class Renderer* wantRender, Vector wantPosition) {
		render = wantRender;
		position = wantPosition;

		gameObjectList.push_back(this);
	};

	virtual void Draw();
	virtual void Start() {};
	virtual void Update() {};
};