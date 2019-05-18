/**
* @file entity.h
*
* @brief The Entity header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

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
#include "input.h"
#include "sdenv2config.h"
#include "vector2.h"
#include "savemanager.h"

/**
* @brief The Entity class
*/
class Entity
{
public:
	Entity(); ///< @brief Constructor of the Entity
	~Entity(); ///< @brief Destructor of the Entity

	glm::vec3 position; ///< @brief the position of entity
	glm::vec3 scale; ///< @brief the scale of entity
	glm::vec3 size; ///< @brief the size of entity ( only 2D )
	glm::vec3 rotation; ///< @brief the rotation of entity

	bool active; ///< @brief the active bool of entity

	Color color; ///< @brief the color of entity

	/// @brief get the mesh of the entity
	/// @return Mesh*
	Mesh* mesh() { return _mesh; };

	/// @brief get the sprite of the entity
	/// @return Sprite*
	Sprite* sprite() { return _sprite; };

	/// @brief get the input
	/// @return Input*
	Input* input() { return _input; };

	/// @brief add the spriteanimator to the entity
	/// @return void
	void addSpriteAnimator() { _spriteanimator = new SpriteAnimator(); };
	/// @brief remove the spriteanimator from the entity
	/// @return void
	void removeSpriteAnimator();
	/// @brief get the spriteanimator from the entity
	/// @return SpriteAnimator*
	SpriteAnimator* spriteAnimator() { return _spriteanimator; };

	/// @brief add a child to the entity
	/// @param the child
	/// @return void
	void addChild(Entity* entity) { _childeren.push_back(entity); };
	/// @brief remove a child from the entity
	/// @param the child
	/// @return void
	void removeChild(Entity* entity);
	/// @brief get the child count
	/// @return int
	int getChildCount() { return _childeren.size(); };
	/// @brief get all the childeren
	/// @return std::vector<Entity*>
	std::vector<Entity*> getChilderen() { return _childeren; };
private:
	Mesh* _mesh; ///< @brief the mesh of the entity
	Sprite* _sprite;  ///< @brief the sprite of the entity
	SpriteAnimator* _spriteanimator;  ///< @brief the spriteanimator of the entity

	Input* _input;  ///< @brief the input

	std::vector<Entity*> _childeren;  ///< @brief the childeren of the entity
};

#endif /* end ENTITY_H */