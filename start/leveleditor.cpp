#include "leveleditor.h"

LevelEditor::LevelEditor(){
	_map = std::vector<EditorTile*>();

	_speed = 120;
	_widht = 50;
	_height = 50;

	_editorsaver = new EditorSaver();

	_editorcanvas = new EditorCanvas();
	this->addCanvas(_editorcanvas);

	_tiles.push_back(Tile("None", "assets/tile_null.png"));
	_tiles.push_back(Tile("Tile 1", "assets/tile_1.png"));
	_tiles.push_back(Tile("Tile 2", "assets/tile_2.png"));
	_tiles.push_back(Tile("Tile 3", "assets/tile_3.png"));
	this->_currentTile = 0;
	_editorcanvas->addTileNameText(_tiles[_currentTile].name);

	this->_currentMode = 0;
	this->_currentEnemyModeStage = 0;
	this->_currentTile = NULL;
	_editorcanvas->addModeText("Mode: " + std::to_string(_currentMode));

	this->_currentLayer = 0;
	_editorcanvas->addLayerText("Layer: " + std::to_string(_currentLayer));

	this->createMap(40, 14);
}

LevelEditor::~LevelEditor(){
	this->saveFile();

	for (int i = 0; i < _map.size(); i++){
		delete _map[i];
	}
	_map.clear();

	delete _editorcanvas;

	delete _editorsaver;
}

void LevelEditor::update(float deltatime){
	this->updateCamera(deltatime);
	this->updateHover(deltatime);
	this->updateClick(deltatime);

	this->updateEditor(deltatime);
}

void LevelEditor::updateEditor(float deltatime) {
	if (input()->getKeyDown(GLFW_KEY_Q)) {
		this->prefTile();
	}else if (input()->getKeyDown(GLFW_KEY_E)) {
		this->nextTile();
	}

	if (input()->getKeyDown(GLFW_KEY_M)) {
		_currentMode++;
		_currentEnemyModeStage = 0;
		_currentEnemyTile = NULL;

		if (_currentMode >= 3) {
			_currentMode = 0;
		}

		_editorcanvas->addModeText("Mode: " + std::to_string(_currentMode));
	}

	if (input()->getKeyDown(GLFW_KEY_L)) {
		_currentLayer++;

		if (_currentLayer >= 3) {
			_currentLayer = 0;
		}

		_editorcanvas->addLayerText("Layer: " + std::to_string(_currentLayer));
	}
}

void LevelEditor::updateCamera(float deltatime){
	if (input()->getKey(GLFW_KEY_W)) {
		camera()->position.y += _speed * deltatime;
	}
	if (input()->getKey(GLFW_KEY_S)) {
		camera()->position.y -= _speed * deltatime;
	}

	if (input()->getKey(GLFW_KEY_D)) {
		camera()->position.x += _speed * deltatime;
	}
	if (input()->getKey(GLFW_KEY_A)) {
		camera()->position.x -= _speed * deltatime;
	}

	if (input()->getKey(GLFW_KEY_LEFT_SHIFT)) {
		_speed = 600;
	}
	else {
		_speed = 300;
	}
}

void LevelEditor::updateClick(float deltatime){
	if (_currentMode == 0) {
		for (int i = 0; i < _map.size(); i++) {
			if (_map[i]->OnClick(camera())) {
				_map[i]->setTexture(_tiles[_currentTile].texture);
				_map[i]->initTile(_currentTile);
				_map[i]->layer = _currentLayer;
			}
			else if (_map[i]->OnHover(camera()) && input()->getMouseButton(GLFW_MOUSE_BUTTON_2)) {
				_map[i]->removeTexture();
				_map[i]->initNone();
				_map[i]->layer = 0;
			}
		}
	}else if(_currentMode == 1){
		for (int i = 0; i < _map.size(); i++) {
			if (_map[i]->OnClick(camera())) {
				_map[i]->setTexture("assets/coin.png");
				_map[i]->initCoin();
				_map[i]->layer = _currentLayer;
			}
			else if (_map[i]->OnHover(camera()) && input()->getMouseButton(GLFW_MOUSE_BUTTON_2)) {
				_map[i]->removeTexture();
				_map[i]->initNone();
				_map[i]->layer = 0;
			}
		}
	}else if (_currentMode == 2) {
		for (int i = 0; i < _map.size(); i++) {
			if (_map[i]->OnHover(camera()) && input()->getMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
				if (_currentEnemyModeStage == 0) {
					_map[i]->setTexture("assets/wood.jpg");
					_map[i]->layer = _currentLayer;
					this->_currentEnemyTile = _map[i];

					_currentEnemyModeStage = 1;
				}else if (_currentEnemyModeStage == 1) {
					this->_currentEnemyTile->walkMinX = _map[i]->x;
					_map[i]->setTexture("assets/wood.jpg");

					_currentEnemyModeStage = 2;
				}else if (_currentEnemyModeStage == 2) {
					this->_currentEnemyTile->walkMaxX = _map[i]->x;
					this->_currentEnemyTile->initEnemy(this->_currentEnemyTile->walkMinX, this->_currentEnemyTile->walkMaxX);
					_map[i]->setTexture("assets/wood.jpg");

					_currentEnemyModeStage = 0;
					_currentEnemyTile = NULL;
				}
			}

			if (_map[i]->OnHover(camera()) && input()->getMouseButton(GLFW_MOUSE_BUTTON_2)) {
				_map[i]->removeTexture();
				_map[i]->initNone();
			}
		}
	}

	std::cout << _currentEnemyModeStage << std::endl;
	
}

void LevelEditor::updateHover(float deltatime){
	for (int i = 0; i < _map.size(); i++) {
		if (_map[i]->OnHover(camera())) {
			_map[i]->setColor(_map[i]->hover);
		}else {
			_map[i]->setColor(_map[i]->normal);
		}
	}
}

void LevelEditor::nextTile(){
	_currentTile++;

	if (_currentTile >= _tiles.size()) {
		_currentTile = 0;
	}

	_editorcanvas->addTileNameText(_tiles[_currentTile].name);
}

void LevelEditor::prefTile(){
	_currentTile--;

	if (_currentTile < 0) {
		_currentTile = _tiles.size() - 1;
	}

	_editorcanvas->addTileNameText(_tiles[_currentTile].name);
}

void LevelEditor::createMap(int sizeX, int sizeY){
	for (int y = 0; y < sizeY; y++){
		for (int x = 0; x < sizeX; x++){
			glm::vec3 position = this->calculatePosition(x, y, _widht, _height);
			glm::vec3 size = glm::vec3(_widht, _height, 0);

			EditorTile* tile = new EditorTile(position, size, "");

			tile->y = y;
			tile->x = x;
			tile->initNone();

			tile->setColor(Color(100,100,100));
			this->addChild(tile);

			_map.push_back(tile);
		}
	}
}

glm::vec3 LevelEditor::calculatePosition(int x, int y, int widht, int height){
	int _x = x * widht + widht;
	int _y = y * height + height;

	return glm::vec3(_x, _y, 0);
}

void LevelEditor::saveFile(){
	std::string data = "Tiles:\n";

	// save tiles
	for (int i = 0; i < _tiles.size(); i++){
		data += "'";
		data += _tiles[i].texture;
		data += "'\n";
	}

	data += "Map:\n";

	std::string layerData = "\nLayer:\n";

	std::string coinData = "\nCoin:\n";
	std::string enemyData = "\nEnemy:\n";

	// save map tile data
	for (int i = 0; i < _map.size(); i++){
		if (_map[i]->isCoin) {
			coinData += std::to_string(_map[i]->x) + "," + std::to_string(_map[i]->y) + "\n";
		}else if (_map[i]->isEnemy) {
			enemyData += std::to_string(_map[i]->x) + "," + std::to_string(_map[i]->y) + "," + std::to_string(_map[i]->walkMinX) + "," + std::to_string(_map[i]->walkMaxX) + "\n";
		}
		layerData += std::to_string(_map[i]->layer);
		data += std::to_string(_map[i]->textureID);

		if (i < _map.size() - 1) {
			data += ",";
			layerData += ",";
		}
	}

	data += layerData;
	data += coinData;
	data += enemyData;

	_editorsaver->saveNewFile(data);
}

void LevelEditor::loadSaveFile(){
}

std::vector<std::string> LevelEditor::split(const std::string & string, char delim) {
	std::vector<std::string> result;
	std::stringstream sstream(string);

	std::string word = "";
	while (std::getline(sstream, word, delim)) {
		result.push_back(word);
	}

	return result;
}


