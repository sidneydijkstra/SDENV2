
#ifndef LEVEL_H
#define LEVEL_H

#include <entity.h>
#include "tile.h"
#include "player.h"
#include "enemy.h"

struct Layout{
	glm::vec2 levelSize;
	glm::vec2 tileSize;
};

class Level : public Entity{
public:
	Level();
	~Level();

	void update(float deltatime);

	// add tile texture
	void addTileTexture(const char* _location);

	// add tile to map
	void addTile();
	// remove tile from map
	void removeTile();

	// add player to map
	void addPlayer(int x, int y);
	// remove player from map
	void removePlayer();

	// add enemy to map
	void addEnemy(int x, int y, int minx, int maxx);

	// load a level from file
	void loadLevelFromFile(const char* _location);
	// load a level from array
	void loadLevelFromArray(std::vector<int> _levelmap, int _mapwidth, int _mapheight, int _tilewidth, int _tileheight);

	// get _grid
	std::vector<Tile*> getGrid();

private:
	// map variables
	std::vector<const char*> _tilesprites;
	std::vector<Tile*> _grid;
	Layout _layout;

	// entitys variables
	Player* _player;

	std::vector<Enemy*> _enemys;
};

#endif /* end LEVEL_H */