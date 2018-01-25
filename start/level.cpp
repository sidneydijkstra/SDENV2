#include "level.h"

Level::Level(){
	_tilesprites.push_back("assets/tile_null.png");

	_player = NULL;
	coinCount = 0;
	healthCount = 3;

	healthTimer = Timer();
	healthTimer.start();
	healthTime = 1.5f;
}

void Level::update(float deltatime){

	// update enemys
	for (int i = 0; i < _enemys.size(); i++) {
		_enemys[i]->update(deltatime, this->getGrid());
	}

	// update coins
	for (int i = 0; i < _coins.size(); i++) {
		_coins[i]->update(deltatime);
	}

	if (_player != NULL) {
		_player->update(deltatime, this->getGrid());

		// check for enemy collision with player
		for (int i = 0; i < _enemys.size(); i++) {
			if (_enemys[i]->collision(_player) && _enemys[i]->topCollision(_player)) {
				_player->addForce(glm::vec3(0,20,0)); // <-- add froce to player to make him bounce of enemy's
				this->removeChild(_enemys[i]);
				delete _enemys[i];
				_enemys.erase(_enemys.begin() + i);
				break;
			}
			else if (_enemys[i]->collision(_player) && _enemys[i]->leftCollision(_player)) {
				_player->position.x -= 1.5f;
				if (healthTimer.seconds() > healthTime) {
					healthTimer.start();
					healthCount--;
				}
			}
			else if (_enemys[i]->collision(_player) && _enemys[i]->rightCollision(_player)) {
				_player->position.x += 1.5f;
				if (healthTimer.seconds() > healthTime) {
					healthTimer.start();
					healthCount--;
				}
			}

		}

		// check for coin collision with player
		for (int i = 0; i < _coins.size(); i++) {
			if (_coins[i]->collision(_player)) {
				coinCount++;

				// remove coin
				this->removeChild(_coins[i]);
				delete _coins[i];
				_coins.erase(_coins.begin() + i);
				break;
			}
		}
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

		fbBottomRender.push_back(_player);

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

void Level::addCoin(int x, int y){
	glm::vec3 position = glm::vec3((_layout.tileSize.x / 2) + _layout.tileSize.x * x, (_layout.tileSize.y / 2) + _layout.tileSize.y * y, 0);
	Coin* c = new Coin(position);

	this->addChild(c);
	_coins.push_back(c);
}

void Level::addEnd(int x, int y, int width, int height){
	glm::vec3 position = glm::vec3((_layout.tileSize.x / 2) + _layout.tileSize.x * x, (_layout.tileSize.y / 2) + _layout.tileSize.y * y, 0);
	Tile* c = new Tile(position,glm::vec3(width, height,0), "assets/tile_end.png");

	this->addChild(c);

	if (end != NULL) {
		this->removeChild(end);
		delete end;
	}

	end = c;
}

void Level::loadLevelFromFile(const char * _location){
}

void Level::loadLevelFromArray(std::vector<int> _levelmap, int _mapwidth, int _mapheight, int _tilewidth, int _tileheight, std::vector<int> layers){
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
			
			// set right render layer
			if (layers[_index] == 0) {
				this->addChild(t);
				fbBottomRender.push_back(t);
			}
			else if (layers[_index] == 1) {
				//fbTopRender.push_back(t);
				this->addChild(t);
			}
			else if (layers[_index] == 2) {
				fbBottomRender.push_back(t);
			}
			
			_grid.push_back(t);
		}
	}

	// set layout to store map and tile size
	_layout.levelSize = glm::vec2(_mapwidth, _mapheight);
	_layout.tileSize = glm::vec2(_tilewidth, _tileheight);
}

std::vector<Tile*> Level::getGrid(){
	return _grid;
}

void Level::playerFollow(Camera * cam){
	if (_player != NULL) {
		cam->position.x = _player->position.x - SWIDTH / 2; // <-- now use 'SWIDTH / 2' need to fix this in engine
	}
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
