#include "ControllerBase.h"
#include "Character.h"
#include <Windows.h>
std::vector<class ControllerBase*> controllerList;

void MessageByLeftClick(tagPOINT mousePos) {};
void MessageByRightClick(tagPOINT mousePos) {

};

void ControllerBase::SetTargetCharacter(Character* wantTarget) {
	owner = wantTarget;
	targetPosition = wantTarget->position;
}

void ControllerBase::SetTargetPosition(Vector wantPosition) {
	owner = nullptr;
	targetPosition = wantPosition;
}

void ControllerBase::Possess(class Character* wantTarget) {
	ControllerBase* preController = wantTarget->myController;

	if (preController != nullptr) { preController->Unpossess(); };

	wantTarget->myController = this;
	owner = wantTarget;
};

void ControllerBase::Unpossess() {
	if (owner == nullptr) return;
	if (owner->myController == this) { owner->myController = nullptr; };

	owner = nullptr;
};


void ControllerBase::Think() {
	//대상이 없으면 정지
	if (owner == nullptr) return;

	owner->MoveTo( Vector(500, 300) );
};