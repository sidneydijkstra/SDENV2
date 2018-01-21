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

	// create level
	_level = new Level();

	// add tile textures level can use
	_level->addTileTexture("assets/tile_1.png");
	_level->addTileTexture("assets/tile_2.png");
	_level->addTileTexture("assets/tile_3.png");
	_level->addTileTexture("assets/head.jpg");

	// level grid
	std::vector<int> levellayout = 
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,1,1,1,0,1,0,0,0,1,
		1,0,0,0,0,0,1,0,0,3,0,0,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,2,0,0,0,0,0,0,0,0,1,
		1,2,2,2,0,0,0,0,2,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,1,0,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,1,0,0,1,1,0,0,1,
		1,0,0,0,0,0,0,1,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	std::vector<int> testlayout =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};


	// load level
	_level->loadLevelFromArray(levellayout, 14, 14, 60, 60);

	// add player
	_level->addPlayer(5, 10);

	// add enemy
	_level->addEnemy(2, 7, 1, 3);
	_level->addEnemy(11, 2, 10, 12);

	// add coins
	_level->addCoin(12,  3);
	_level->addCoin(10,  7);
	_level->addCoin(10, 11);

	// add level as child
	this->addChild(_level);
}	

void MyScene::update(float deltatime) {
	// update level
	_level->update(deltatime);
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
}

