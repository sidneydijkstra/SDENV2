#include "entity.h"

Entity::Entity(){
	_mesh = new Mesh();
	_sprite = new Sprite();
	_input = Input::getInstance();

	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	size = glm::vec3(1, 1, 1);
	rotation = glm::vec3(0, 0, 0);

	color = Color();

	_spriteanimator = NULL;

	active = true;
}

void Entity::removeSpriteAnimator() {
	if (_spriteanimator != NULL) {
		delete _spriteanimator;
		_spriteanimator = NULL;
	}
}

void Entity::removeChild(Entity * entity){
	for (int i = 0; i < _childeren.size(); i++) { 
		if (_childeren[i] == entity) { 
			_childeren.erase(_childeren.begin() + i); 
			break; 
		}
	}
}

Entity::~Entity(){
	// remove mesh sprite and spriteanimator if entity has one
	delete _mesh;
	delete _sprite;
	this->removeSpriteAnimator();

	// remove childeren
	/*
	for (int i = 0; i < _childeren.size(); i++){
		delete _childeren[i];
	}
	*/
	_childeren.clear();
}


