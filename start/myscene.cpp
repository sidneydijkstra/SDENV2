#include "myscene.h"


MyScene::MyScene(){
	this->setSceneMode(SCENE2D); // <-- set scene mode

	// create top framebuffer
	fbTop = new FrameBuffer();
	fbTop->position = glm::vec3(SWIDTH/ 2, (SHEIGHT / 4) * 3, 0);
	fbTop->size = glm::vec3(SWIDTH / 2, SHEIGHT / 4, 0);
	fbTop->background = Color(255, 255, 255);
	this->addFramebuffer(fbTop);

	// create bottom framebuffer
	fbBottom = new FrameBuffer();
	fbBottom->position = glm::vec3(SWIDTH / 2, SHEIGHT / 4, 0);
	fbBottom->size = glm::vec3(SWIDTH / 2, SHEIGHT / 4, 0);
	fbBottom->rotation.z = 1.570796327f * 2;
	fbBottom->rotation.y = 1.570796327f * 2;
	fbBottom->background = Color(0, 0, 0);

	fbBottom->addCostumShader("shaders/framebuffer.vert", "shaders/framebuffer_costumshader.frag");

	this->addFramebuffer(fbBottom);

	// create hud canvas
	_hudCanvas = new HudCanvas();
	this->addCanvas(_hudCanvas);

	_endCanvas = new EndCanvas();
	this->addCanvas(_endCanvas);
	_endCanvas->active = false;

	_menuCanvas = new MenuCanvas();
	this->addCanvas(_menuCanvas);
	_menuCanvas->active = false;

	_level = new Level();

	// add level as child
	this->addChild(_level);
	_level->next = true;

	//fbTop->addRenderEntity(_level->fbTopRender);
	fbBottom->addRenderEntity(_level->fbBottomRender);

	delete _level;
	fbBottom->removeRenderEntitys();
	this->removeChild(_level);
	_level = new Level();
	fbBottom->addRenderEntity(_level->fbBottomRender);
	pause = true;

	_menuCanvas->active = true;
}	

void MyScene::update(float deltatime) {
	
	if (pause) {
		if (_endCanvas->active) {
			_endCanvas->update();
		}

		if (_menuCanvas->active) {
			_menuCanvas->update();
		}
		

		if (_endCanvas->_back->OnClick()) {
			_endCanvas->active = false;
			_menuCanvas->active = true;
		}

		if (_menuCanvas->_start->OnClick()) {
			_menuCanvas->active = false;
			_level->levelTimer.start();
			this->addChild(_level);
			pause = false;
		}

		return;
	}

	if (_level->dead) {
	}
	if (_level->next) {
		delete _level;
		fbBottom->removeRenderEntitys();
		this->removeChild(_level);
		_level = new Level();
		fbBottom->addRenderEntity(_level->fbBottomRender);
		_endCanvas->active = true;
		_endCanvas->loadScore();

		pause = true;
	}

	// update level
	_level->update(deltatime);

	// use camera movement
	_level->playerFollow(this->camera());

	// update HUD
	_hudCanvas->addCoin("Coins: " + std::to_string(_level->coinCount));
	_hudCanvas->addHealth("Health: " + std::to_string(_level->healthCount));
	_hudCanvas->addTimer("TIme: " + std::to_string(_level->levelTimer.seconds()));
}

void MyScene::loadLevelA()
{
	// create level
	if (_level != NULL) {
		delete _level;
	}

	_level = new Level();

	
}

void MyScene::loadLevelB()
{
	// create level
	if (_level != NULL) {
		delete _level;
	}

	_level = new Level();

	// add tile textures level can use
	_level->addTileTexture("assets/tile_1.png");
	_level->addTileTexture("assets/tile_2.png");
	_level->addTileTexture("assets/tile_3.png");

	// level grid

	std::vector<int> levellayout =
	{
		2,1,1,1,2,1,1,1,2,2,1,1,2,2,1,1,1,2,2,1,1,2,2,1,1,2,2,1,1,1,2,1,1,2,2,1,1,2,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,2,0,0,0,3,3,2,0,0,2,3,0,0,0,0,0,0,0,2,0,0,0,0,1,1,2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,3,3,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,2,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,2,1,2,2,1,1,2,2,1,1,2,2,1,1,2,1,1,2,2,1,1,2,2,2,1,1,1,2,2,1,0,0,0,0,1,1,1,2,0,0,3,2,1,1,0,0,0,0,0,2,1,0,0,0,1,0,0,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,2,1,0,0,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,2,1,0,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1,1,0,0,3,0,0,0,3,3,3,0,1,1,2,1,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,2,0,0,0,0,0,0,0,0,0,0,1,2,2,1,1,2,2,1,1,2,1,1,2,2,1,1,2,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,1,1,1,2
	};

	std::vector<int> renderlayout =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,2,2,2,0,0,1,2,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,2,0,2,1,1,1,0,0,2,0,0,1,1,0,0,0,1,0,0,0,2,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,2,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,0,0,0,2,2,2,0,1,1,1,1,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};


	// load level
	_level->loadLevelFromArray(levellayout, 40, 14, 60, 60, renderlayout);

	// add player
	_level->addPlayer(2, 4);

	// add enemy
	_level->addEnemy(9, 3, 8, 10);
	_level->addEnemy(35, 3, 27, 37);
	_level->addEnemy(24, 9, 23, 25);

	// add 
	_level->addCoin(15, 1);
	_level->addCoin(38, 1);
	_level->addCoin(7, 3);
	_level->addCoin(9, 7);
	_level->addCoin(21, 7);
	_level->addCoin(27, 9);
	_level->addCoin(37, 11);
	_level->addCoin(38, 11);

	// add end
	_level->addEnd(1, 7, 30, 30);

	// add level as child
	this->addChild(_level);

	//fbTop->addRenderEntity(_level->fbTopRender);
	fbBottom->addRenderEntity(_level->fbBottomRender);
}

void MyScene::loadLevelC()
{
	// create level
	if (_level != NULL) {
		delete _level;
	}

	_level = new Level();

	// add tile textures level can use
	_level->addTileTexture("assets/tile_1.png");
	_level->addTileTexture("assets/tile_2.png");
	_level->addTileTexture("assets/tile_3.png");

	// level grid

	std::vector<int> levellayout =
	{
		1,1,3,3,3,1,1,1,1,3,3,1,1,3,3,3,1,1,3,3,1,1,3,1,1,1,3,1,1,3,3,1,1,3,3,1,1,1,3,3,1,0,0,0,0,0,0,0,0,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,1,2,0,0,0,0,0,0,0,2,3,3,3,0,0,0,0,0,0,0,1,1,1,2,1,3,0,0,0,0,1,2,2,0,0,0,0,0,0,2,1,1,0,0,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,2,0,0,0,0,0,3,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,1,0,0,0,2,0,0,0,3,0,0,0,1,0,0,0,3,0,0,0,2,0,0,0,3,0,0,0,2,0,0,0,3,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,3,3,1,1,3,3,1,3,1,1,3,1,3,3,1,3,3,1,3,1,1,1,3,3,3,3,1,1,1,3,3,3,1,1,3,1,1,1,1
	};

	std::vector<int> renderlayout =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,2,0,0,0,1,0,0,0,2,0,0,0,1,0,0,0,2,0,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};


	// load level
	_level->loadLevelFromArray(levellayout, 40, 14, 60, 60, renderlayout);

	// add player
	_level->addPlayer(3, 4);

	// add enemy
	_level->addEnemy(27, 1, 11, 13);
	_level->addEnemy(26, 3, 18, 24);
	_level->addEnemy(15, 7, 6, 8);

	// add coins
	_level->addCoin(15, 1);
	_level->addCoin(23, 1);
	_level->addCoin(38, 4);
	_level->addCoin(6, 5);
	_level->addCoin(25, 7);

	// add end
	_level->addEnd(38, 8, 24, 16);

	// add level as child
	this->addChild(_level);

	//fbTop->addRenderEntity(_level->fbTopRender);
	fbBottom->addRenderEntity(_level->fbBottomRender);
}

MyScene::~MyScene(){
	// remove childeren, framebuffers and text
	this->removeChild(_level);
	this->removeFramebuffer(fbTop);
	this->removeFramebuffer(fbBottom);
	// delete pointers
	delete _level;
	delete fbTop;
	delete fbBottom;

	delete _hudCanvas;
	delete _endCanvas;
	delete _menuCanvas;
}

