#pragma once

#include "Movable.h"
#include <string>

class Character : public Movable {
public:
	class ControllerBase* myController = nullptr;

	std::wstring name;
	//���� �����
	int healthCurrent;
	//�ִ� �����
	int healthMax;

	//�ֱ�?
	bool isDie = false;

	Character(class Renderer* wantRender, Vector wantLocation, float wantSpeed, std::wstring wantName, int wantHealth) 
		: Movable(wantRender, wantLocation, wantSpeed) {
		name = wantName;
		healthCurrent = healthMax = wantHealth;
	}
};