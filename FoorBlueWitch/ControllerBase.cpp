#include "ControllerBase.h"
#include "Character.h"
std::vector<class ControllerBase*> controllerList;

void ControllerBase::Possess(class Character* wantTarget) {
	ControllerBase* preController = wantTarget->myController;

	if (preController != nullptr) { preController->Unpossess(); };

	wantTarget->myController = this;
	target = wantTarget;
};

void ControllerBase::Unpossess() {
	if (target == nullptr) return;
	if (target->myController == this) { target->myController = nullptr; };

	target = nullptr;
};


void ControllerBase::Think() {
	//����� ������ ����
	if (target == nullptr) return;

	target->MoveTo( Vector(500, 300) );
};