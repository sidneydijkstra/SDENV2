
#ifndef LEVEL_H
#define LEVEL_H

#include <entity.h>
#include <camera.h>
#include "tile.h"
#include "player.h"
#include "enemy.h"
#include "coin.h"
#include "framebuffer.h"
#include "timer.h"

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

	// add player to map
	void addPlayer(int x, int y);
	// remove player from map
	void removePlayer();

	// add enemy to map
	void addEnemy(int x, int y, int minx, int maxx);

	// add coin from map
	void addCoin(int x, int y);

	// add the end position
	void addEnd(int x, int y, int width, int height);

	// load a level from file
	void loadLevelFromFile(const char* _location);
	// load a level from array
	void loadLevelFromArray(std::vector<int> _levelmap, int _mapwidth, int _mapheight, int _tilewidth, int _tileheight, std::vector<int> layers);

	// get _grid
	std::vector<Tile*> getGrid();

	// move camera with player
	void playerFollow(Camera* cam);

	// get player and enemys
	Player* getPlayer() { return _player; };
	std::vector<Enemy*> getEnemys() { return _enemys; };

	// the framebuffers
	std::vector<Entity*> fbTopRender;
	std::vector<Entity*> fbBottomRender;

	void reset();

	// level timer
	Timer levelTimer;

	// hud values
	int coinCount;
	int healthCount;

	bool next;
	bool dead;
private:
	// map variables
	std::vector<const char*> _tilesprites;
	std::vector<Tile*> _grid;
	Layout _layout;

	// entitys variables
	Player* _player;

	// list of enemys
	std::vector<Enemy*> _enemys;
	// list of coins
	std::vector<Coin*> _coins;
	// end pos
	Tile* end;

	Timer healthTimer;
	float healthTime;
};

#endif /* end LEVEL_H */
