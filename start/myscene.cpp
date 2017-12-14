#include "myscene.h"

Text* text;
FrameBuffer* fb;
FrameBuffer* fb2;

MyScene::MyScene(){
	// render text
	text = new Text("assets/arial.ttf", 1, glm::vec3(0,1,0));
	text->message = "QWERTYUIOPASDFGHJKLZXCVBNM!";
	text->setColorLerp(glm::vec3(1, 0, 0), glm::vec3(0, 0, 1));
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

	// spawn tile
	tile = new Tile(glm::vec3(SWIDTH/2, 100, 0), glm::vec3(100, 30, 0), "assets/gold.jpg");
	this->addChild(tile);
}	

void MyScene::update(float deltatime) {
	player->update(deltatime, tile);
}

MyScene::~MyScene(){
}

