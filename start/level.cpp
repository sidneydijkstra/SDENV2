#include "level.h"

Level::Level(){
	_tilesprites.push_back("assets/tile_null.png");

	_player = NULL;
}

void Level::update(float deltatime){
	if (_player != NULL) {
		_player->update(deltatime, this->getGrid());
	}

	for (int i = 0; i < _enemys.size(); i++){
		_enemys[i]->update(deltatime, this->getGrid());
	}

}

void Level::addTileTexture(const char * _location){
	_tilesprites.push_back(_location);
}

void Level::addPlayer(int x, int y){
	if (x <= _layout.levelSize.x && x >= 0 && y <= _layout.levelSize.y && y >= 0) {
		// remove player
		this->removePlayer();
		
		// create new player
		_player = new Player();
		float posx = (_layout.tileSize.x / 2) + _layout.tileSize.x * x;
		float posy = (_layout.tileSize.y / 2) + _layout.tileSize.y * y;
		_player->position = glm::vec3(posx, posy, 0);

		// add player as child
		this->addChild(_player);
	}
	
}

void Level::removePlayer(){
	if (_player != NULL) {
		this->removeChild(_player);
		delete _player;
		_player = NULL;
	}
}

void Level::addEnemy(int x, int y, int minx, int maxx){
	Enemy* e = new Enemy(_player, (_layout.tileSize.x / 2) + _layout.tileSize.x * minx, (_layout.tileSize.x / 2) + _layout.tileSize.x * maxx);
	float posx = (_layout.tileSize.x / 2) + _layout.tileSize.x * x;
	float posy = (_layout.tileSize.y / 2) + _layout.tileSize.y * y;
	e->position = glm::vec3(posx, posy, 0);

	this->addChild(e);
	_enemys.push_back(e);
}

void Level::loadLevelFromFile(const char * _location){
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

	// set layout to store map and tile size
	_layout.levelSize = glm::vec2(_mapwidth, _mapheight);
	_layout.tileSize = glm::vec2(_tilewidth, _tileheight);
}

std::vector<Tile*> Level::getGrid(){
	return _grid;
}

Level::~Level(){
	// delete grid and clear vector's
	for (int i = 0; i < _grid.size(); i++) {
		delete _grid[i];
	}
	_grid.clear();
	_tilesprites.clear();

	// delete player
	this->removePlayer();

	// delete enemys
	for (int i = 0; i < _enemys.size(); i++){
		delete _enemys[i];
	}
	_enemys.clear();
}
