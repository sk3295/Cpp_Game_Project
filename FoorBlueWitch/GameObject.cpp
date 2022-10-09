#include "GameObject.h"
#include "D2d.h"

std::vector<GameObject*> gameObjectList;

void GameObject::Draw() {
	render->Draw(position.x, position.y);
}