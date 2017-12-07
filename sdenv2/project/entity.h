
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "sprite.h"
#include "spriteanimator.h"
#include "color.h"
#include "sdenv2config.h"

class Entity
{
public:
	Entity();
	~Entity();

	// mesh variabels
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	// is entity active
	bool active;

	// entity color
	Color color;

	// get mesh
	Mesh* mesh() { return _mesh; };

	// get sprite
	Sprite* sprite() { return _sprite; };

	// add sprite animator
	void addSpriteAnimator() { _spriteanimator = new SpriteAnimator(_sprite); };
	// remove sprite animator
	void removeSpriteAnimator();
	// get sprite animator
	SpriteAnimator* spriteAnimator() { return _spriteanimator; };

	// entity childeren functions
	void addChild(Entity* entity) { _childeren.push_back(entity); };
	void removeChild(Entity* entity) { for (int i; i < _childeren.size(); i++) { if (_childeren[i] == entity) { _childeren.erase(_childeren.begin() + i); delete entity; break; }; }; };
	int getChildCount() { return _childeren.size(); };
	std::vector<Entity*> getChilderen() { return _childeren; };
private:
	Mesh* _mesh;
	Sprite* _sprite;
	SpriteAnimator* _spriteanimator;

	std::vector<Entity*> _childeren;
};

#endif /* end ENTITY_H */