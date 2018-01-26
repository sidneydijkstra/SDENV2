#include "level.h"

Level::Level(){
	_tilesprites.push_back("assets/tile_null.png");

	_player = NULL;
	end = NULL;
	coinCount = 0;
	healthCount = 3;

	levelTimer = Timer();
	levelTimer.start();

	healthTimer = Timer();
	healthTimer.start();
	healthTime = 1.5f;

	next = false;
	dead = false;

	// add tile textures level can use
	this->addTileTexture("assets/tile_1.png");
	this->addTileTexture("assets/tile_2.png");
	this->addTileTexture("assets/tile_3.png");

	// level grid

	std::vector<int> levellayout =
	{
		1,1,1,1,1,3,3,1,1,3,3,1,1,1,1,1,3,1,1,1,3,3,3,1,1,3,3,1,1,1,3,3,3,1,1,1,3,3,1,1,3,0,0,0,3,0,0,0,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,0,0,0,0,2,1,2,0,0,0,0,0,0,0,0,0,0,0,2,2,1,2,2,3,3,2,1,2,3,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1,2,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,0,0,0,0,1,2,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,3,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,0,0,2,2,1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,0,0,1,2,3,3,1,0,0,0,0,0,2,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,3,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,2,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,3,3,1,1,3,3,1,1,3,1,1,3,1,1,1,3,1,1,3,3,1,1,3,3,1,1,1,3,3,1,1,1,1,3,3,1,1,1,3
	};

	std::vector<int> renderlayout =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,2,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};


	// load level
	this->loadLevelFromArray(levellayout, 40, 14, 60, 60, renderlayout);

	// add player
	this->addPlayer(5, 11);

	// add enemy
	this->addEnemy(27, 1, 11, 13);
	this->addEnemy(26, 3, 18, 24);
	this->addEnemy(15, 7, 6, 8);

	// add coins
	this->addCoin(1, 1);
	this->addCoin(2, 1);
	this->addCoin(21, 1);
	this->addCoin(31, 1);
	this->addCoin(1, 2);
	this->addCoin(2, 2);
	this->addCoin(13, 4);
	this->addCoin(30, 5);
	this->addCoin(13, 7);
	this->addCoin(38, 7);
	this->addCoin(24, 10);
	this->addCoin(1, 11);

	// add end
	this->addEnd(38, 12, 30, 30);
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

		// check for at end
		if (end != NULL && end->collision(_player)) {
			std::cout << "end" << std::endl;
			SaveManager::getInstance()->setValue("LEVEL_TIMER", std::to_string(levelTimer.seconds()));
			next = true;
		}

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

				if (healthCount <= 0) {
					dead = true;
				}
			}
			else if (_enemys[i]->collision(_player) && _enemys[i]->rightCollision(_player)) {
				_player->position.x += 1.5f;
				if (healthTimer.seconds() > healthTime) {
					healthTimer.start();
					healthCount--;
				}

				if (healthCount <= 0) {
					dead = true;
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

void Level::reset(){
	fbTopRender.clear();
	fbBottomRender.clear();

	this->removePlayer();

	for (int i = 0; i < _enemys.size(); i++){
		this->removeChild(_enemys[i]);
		delete _enemys[i];
		_enemys.erase(_enemys.begin() + i);
		break;
	}
	_enemys.clear();

	for (int i = 0; i < _coins.size(); i++) {
		this->removeChild(_coins[i]);
		delete _coins[i];
		_coins.erase(_coins.begin() + i);
		break;
	}
	_coins.clear();

	for (int i = 0; i < _grid.size(); i++){
		this->removeChild(_grid[i]);
		delete _grid[i];
		_grid.erase(_grid.begin() + i);
		break;
	}

	if (end != NULL) {
		delete end;
		end = NULL;
	}

	_tilesprites.clear();
	_tilesprites.push_back("assets/tile_null.png");

	coinCount = 0;
	healthCount = 3;

	levelTimer = Timer();
	levelTimer.start();

	healthTimer = Timer();
	healthTimer.start();
	healthTime = 1.5f;

	next = false;
	dead = false;
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
