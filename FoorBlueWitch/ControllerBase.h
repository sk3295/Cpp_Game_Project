#pragma once

#include <vector>			
#include "Math.h"			
#include "FoorBlueWitch.h"  

//       컨트롤러를 가지고 있는 가변배열
extern std::vector<class ControllerBase*> controllerList;

void MessageByLeftClick(struct tagPOINT mousePos);
void MessageByRightClick(struct tagPOINT mousePos);

extern class ControllerBase* player;

//캐릭터를 다루는 컨트롤러
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