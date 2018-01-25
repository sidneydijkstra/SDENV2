#pragma once

#ifndef EDITORTILE_H
#define EDITORTILE_H


#include <scene.h>
#include <mesh.h>
#include <timer.h>
#include "player.h"
#include "tile.h"
#include "level.h"
#include "enemy.h"

class EditorTile : public Entity
{
public:
	EditorTile(glm::vec3 _position, glm::vec3 _size, const char* _texture);
	virtual ~EditorTile();

	virtual void update(float deltatime);

	void setTexture(const char* _texture);
	void setColor(Color _color);
	void setHoverColor(Color _color);
	void removeTexture();

	bool OnClick(Camera* cam);
	bool OnHover(Camera* cam);

	Color normal;
	Color hover;

	void initNone();
	void initTile(int _textureID);
	void initCoin();
	void initEnemy(int minX, int maxX);

	bool isTile;
	bool isCoin;
	bool isEnemy;

	int textureID;

	int x;
	int y;

	int walkMinX;
	int walkMaxX;

	int layer; // 0 = all, 1 == top, 2 == bottom


private:
};

#endif /* end EDITORTILE_H */
