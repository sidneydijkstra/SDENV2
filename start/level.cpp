#include "level.h"

Level::Level(){
	_tilesprites.push_back("assets/tile_null.png");
}

Level::~Level()
{
}

void Level::addTileTexture(const char * _location){
	_tilesprites.push_back(_location);
}

void Level::loadLevelFromFile(const char * _location)
{
}

void Level::loadLevelFromArray(std::vector<int> _levelmap, int _mapwidth, int _mapheight, int _tilewidth, int _tileheight){
	for (int y = 0; y < _mapheight; y++){
		for (int x = 0; x < _mapwidth; x++) {
			int _index = y * _mapwidth + x;

			// get tile texture
			const char* loc = "";
			if (_levelmap[_index] >= _tilesprites.size()) { // if texture number does not exist set null texture
				loc = _tilesprites[0];
			}else if(_levelmap[_index] == 0){
				continue; // dont spawn a tile and go to next
			}else {
				loc = _tilesprites[_levelmap[_index]]; // else set _levelmap number to tile sprite
			}

			// get tile position4
			float posx = (_tilewidth/2) + _tilewidth * x;
			float posy = (_tileheight/2) + _tileheight * y;

			// create tile
			Tile* t = new Tile(glm::vec3(posx, posy, 0), glm::vec3(_tilewidth / 2, _tileheight / 2, 0), loc);
			_grid.push_back(t);
			this->addChild(t);
		}
	}
}

std::vector<Tile*> Level::getGrid(){
	return _grid;
}
