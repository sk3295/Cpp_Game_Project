#pragma once

#include <vector>			
#include "Math.h"			
#include "FoorBlueWitch.h"  

//       ��Ʈ�ѷ��� ������ �ִ� �����迭
extern std::vector<class ControllerBase*> controllerList;

void MessageByLeftClick(struct tagPOINT mousePos);
void MessageByRightClick(struct tagPOINT mousePos);

extern class ControllerBase* player;

//ĳ���͸� �ٷ�� ��Ʈ�ѷ�
class ControllerBase {
	class Character* owner;
	Vector targetPosition;
public:
	ControllerBase() {
		controllerList.push_back(this);
	}

	void Possess(class Character* wantTarget);

	void Unpossess();

	void Think();

	void SetTargetCharacter(class Character* wantTarget);
	void SetTargetPosition(Vector wantPosition);
};