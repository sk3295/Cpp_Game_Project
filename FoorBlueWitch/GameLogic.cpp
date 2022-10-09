#include "FoorBlueWitch.h"
#include "GameObject.h"
#include "ControllerBase.h"
#include "Character.h"
#include "D2d.h"

void GameStart() {
	Character* testCharacter = 
		new Character (
			new Renderer(L"ÁÖÀÎ°ø±âº»", SourceType::Animator),
			Vector(0,0),
			100,
			L"ÆÄ¶û¸¶³à",
			100
		);

	( new ControllerBase() )->Possess(testCharacter);
}

void GameUpdate() {
	for (ControllerBase* current : controllerList)	current->Think();
	for (GameObject* current : gameObjectList)		current->Update();
}

void GameEnd() {}