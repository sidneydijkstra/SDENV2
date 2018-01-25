#include "editortile.h"

EditorTile::EditorTile(glm::vec3 _position, glm::vec3 _size, const char* _texture){
	this->mesh()->loadQuad();

	this->position = _position;
	this->scale = _size / 2.0f;
	this->sprite()->loadTexture(_texture, 0, 0);
	this->sprite()->removeTexture();

	this->hover = Color(100,100,100);
	this->normal = Color(220,220,220);

	layer = 0;
}

EditorTile::~EditorTile()
{
}

void EditorTile::update(float deltatime){
	
}

void EditorTile::setTexture(const char * _texture){
	this->sprite()->loadTexture(_texture, 0, 0);
}

void EditorTile::setColor(Color _color){
	this->color = _color;
}

void EditorTile::setHoverColor(Color _color){
	hover = _color;
}

void EditorTile::removeTexture(){
	this->sprite()->removeTexture();
}

bool EditorTile::OnClick(Camera * cam){
	float x = (input()->getMouseX() + cam->position.x);
	float y = (input()->getMouseY() + cam->position.y);

	if (x > this->position.x - this->scale.x && x < this->position.x + this->scale.x && y < this->position.y + this->scale.y && y > this->position.y - this->scale.y && input()->getMouseButton(GLFW_MOUSE_BUTTON_1)) {
		return true;
	}
	return false;
}

bool EditorTile::OnHover(Camera * cam){
	float x = (input()->getMouseX() + cam->position.x);
	float y = (input()->getMouseY() + cam->position.y);

	if (x > this->position.x - this->scale.x && x < this->position.x + this->scale.x &&
		y < this->position.y + this->scale.y && y > this->position.y - this->scale.y) {
		return true;
	}
	return false;
}

void EditorTile::initNone(){
	textureID = 0;

	walkMinX = 0;
	walkMaxX = 0;

	isTile = false;
	isEnemy = false;
	isCoin = false;
}

void EditorTile::initTile(int _textureID){
	textureID = _textureID;

	walkMinX = 0;
	walkMaxX = 0;

	isTile = true;
	isEnemy = false;
	isCoin = false;
}

void EditorTile::initCoin(){
	textureID = 0;

	walkMinX = 0;
	walkMaxX = 0;

	isTile = false;
	isEnemy = false;
	isCoin = true;
}

void EditorTile::initEnemy(int minX, int maxX){
	textureID = 0;

	walkMinX = minX;
	walkMaxX = maxX;

	isTile = false;
	isEnemy = true;
	isCoin = false;
}
