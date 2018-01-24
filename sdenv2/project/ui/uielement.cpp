#include "uielement.h"

UIElement::UIElement(){
	_mesh = new Mesh();
	_mesh->loadQuad();

	_sprite = new Sprite();

	_input = Input::getInstance();

	this->position = glm::vec3(0,0,0);
	this->rotation = glm::vec3(0, 0, 0);
	this->size = glm::vec3(0, 0, 0);

	color = Color(255,255,0);

	this->active = true;

	//sprite()->loadTexture("assets/tile_1.png", 0, 0);
}

bool UIElement::OnHovor(){
	float x = input()->getMouseX();
	float y = input()->getMouseY();

	glm::vec3 pos = this->getWorldPosition();

	float right = pos.x + this->size.x;
	float left = pos.x - this->size.x;

	float top = pos.y + this->size.y;
	float bottom = pos.y - this->size.y;

	if (x > left && x < right && y > bottom && y < top) {
		return true;
	}

	return false;
}

bool UIElement::OnHold(){
	if (this->OnHovor() && input()->getMouseButton(GLFW_MOUSE_BUTTON_1)) {
		return true;
	}
	return false;
}

bool UIElement::OnClick() {
	if (this->OnHovor() && input()->getMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
		return true;
	}
	return false;
}

UIElement::~UIElement(){
	delete _mesh;
	delete _sprite;
}
