#pragma once

#include <vector>			
#include "Math.h"			
#include "FoorBlueWitch.h"  

//       ��Ʈ�ѷ��� ������ �ִ� �����迭
extern std::vector<class ControllerBase*> controllerList;

//ĳ���͸� �ٷ�� ��Ʈ�ѷ�
class ControllerBase {
	class Character* target;

public:
	ControllerBase() {
		controllerList.push_back(this);
	}

	void Possess(class Character* wantTarget);

	void Unpossess();

	void Think();
};