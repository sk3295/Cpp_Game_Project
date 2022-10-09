#pragma once

#include "resource.h"

extern bool gameRunning;

//Frame Per Seconds  1�ʿ� �� ������ ����
// 30 60 144
#define FPS 60
#define FRAMETIME 1.0f / FPS

extern float deltaTime;   
extern unsigned long lastUpdateTime;

void GameStart();
void GameUpdate();
void GameEnd();