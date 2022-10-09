#include "Movable.h"
#include "FoorBlueWitch.h"

void Movable::Update() {
	float currentSpeed = speed * deltaTime; // 1 frame �� �̵� �ӵ�
	Vector currentMove = targetPosition - position;

	// ���� �����ϴ� �Ÿ����� �ӵ��� ���� ���
	if (currentMove.Magnitude() < currentSpeed) position = targetPosition;
	else position += currentMove.normalized() * currentSpeed;
}