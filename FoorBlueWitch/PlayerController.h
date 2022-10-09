#pragma once
#include "ControllerBase.h"

class PlayerController : public ControllerBase {
public:
	PlayerController() : ControllerBase() {
		if (player == nullptr) player = this;
	}
};
