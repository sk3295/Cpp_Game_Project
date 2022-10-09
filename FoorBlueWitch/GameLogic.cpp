#include "FoorBlueWitch.h"
#include "GameObject.h"
#include "ControllerBase.h"
#include "PlayerController.h"
#include "Character.h"
#include "D2d.h"

void GameStart() {
	Character* testCharacter = 
		new Character (
			new Renderer(L"���ΰ��⺻", SourceType::Animator),
			Vector(0,0),
			80,
			L"�Ķ�����",
			100
		);

	( new PlayerController() )->Possess(testCharacter);
}

void GameUpdate() {
	for (ControllerBase* current : controllerList)	current->Think();
	for (GameObject* current : gameObjectList)		current->Update();
}

void GameEnd() {}