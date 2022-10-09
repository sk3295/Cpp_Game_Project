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
	// > �ڵ� �ڸ��� ��� ����, �ٿ��ֱ� �Ͽ� ä���־��ش�.
	inline virtual void MoveTo(Vector wantDestination) {
		// �������� ���� ����
		targetPosition = wantDestination;
	}
};