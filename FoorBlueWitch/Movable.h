#pragma once
#include "GameObject.h"

class Movable : public GameObject {
public:
	Vector targetPosition;
	float speed;

	Movable(class Renderer* wantRender, Vector wantPosition, float wantSpeed) : GameObject(wantRender, wantPosition) {
		speed = wantSpeed;
	}

	void Update();

	// inline
	// > 코드 자리에 대신 복사, 붙여넣기 하여 채워넣어준다.
	inline virtual void MoveTo(Vector wantDestination) {
		// 목적지로 가는 방향
		targetPosition = wantDestination;
	}
};