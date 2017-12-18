#include "myscene.h"

Text* text;
FrameBuffer* fb;
FrameBuffer* fb2;

MyScene::MyScene(){
	// render text
	text = new Text("assets/arial.ttf", 0.3f, glm::vec3(0,1,0));
	text->message = "QWERTYUIOPASDFGHJKLZXCVBNM!";
	text->setColorLerp(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1));
	text->position.y = 100;
	this->addText(text);

	// create top framebuffer
	fb2 = new FrameBuffer();
	fb2->position = glm::vec3(SWIDTH/ 2, (SHEIGHT / 4) * 3, 0);
	fb2->size = glm::vec3(SWIDTH / 2, SHEIGHT / 4, 0);
	fb2->background = Color(255, 255, 255);
	this->addFramebuffer(fb2);

	// create bottom framebuffer
	fb = new FrameBuffer();
	fb->position = glm::vec3(SWIDTH / 2, SHEIGHT / 4, 0);
	fb->size = glm::vec3(SWIDTH / 2, SHEIGHT / 4, 0);
	fb->rotation.z = 1.570796327f * 2;
	fb->rotation.y = 1.570796327f * 2;
	fb->background = Color(0, 100, 0);
	this->addFramebuffer(fb);

	// create player
	player = new Player();
	this->addChild(player);

	// create enemy
	enemy = new Enemy(player);
	this->addChild(enemy);

	// spawn tile
	_level = new Level();

	_level->addTileTexture("assets/tile_1.png");
	_level->addTileTexture("assets/tile_2.png");
	_level->addTileTexture("assets/tile_3.png");
	_level->addTileTexture("assets/tile_4.png");

	std::vector<int> layout = 
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,1,1,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,3,0,0,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,2,2,2,0,0,0,0,2,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,1,0,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
	_level->loadLevelFromArray(layout, 14, 10, 60, 60);
	this->addChild(_level);
}	

void MyScene::update(float deltatime) {
	enemy->update(deltatime);
	player->update(deltatime, _level->getGrid());
}

MyScene::~MyScene(){
}

