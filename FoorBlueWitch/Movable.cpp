#include "Movable.h"
#include "FoorBlueWitch.h"

void Movable::Update() {
	float currentSpeed = speed * deltaTime; // 1 frame 당 이동 속도
	Vector currentMove = targetPosition - position;

	// 만일 가야하는 거리보다 속도가 빠를 경우
	if (currentMove.Magnitude() < currentSpeed) position = targetPosition;
	else position += currentMove.normalized() * currentSpeed;
}