
#ifndef LEVEL_H
#define LEVEL_H

#include <entity.h>
#include "tile.h"

class Level : public Entity{
public:
	Level();
	~Level();

	// add tile texture
	void addTileTexture(const char* _location);

	// add tile to map
	void addTile();
	// remove tile from map
	void removeTile();

	// load a level from file
	void loadLevelFromFile(const char* _location);
	// load a level from array
	void loadLevelFromArray(std::vector<int> _levelmap, int _mapwidth, int _mapheight, int _tilewidth, int _tileheight);

	// get _grid
	std::vector<Tile*> getGrid();

private:
	std::vector<const char*> _tilesprites;
	std::vector<Tile*> _grid;
};

#endif /* end LEVEL_H */
