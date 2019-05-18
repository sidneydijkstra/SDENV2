#include "map.h"

Map::Map() {
}

Map::~Map() {
}

void Map::update(float deltatime) {
}

void Map::generateGrid(){
	_grid = std::vector<std::vector<Tile*>>();
	int tileSize = 20;

	for (int i = 0; i < 10; i++){
		std::vector<Tile*> tempList = std::vector<Tile*>();
		for (int j = 0; j < 10; j++){
			Tile* tempTile = new Tile(40 * i, 40 * j, 20, 20);
			this->addChild(tempTile);
			tempList.push_back(tempTile);
		}
		_grid.push_back(tempList);
	}
}
