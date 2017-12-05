#include "myscene.h"
#include "sprite.h"

Text* text;

MyScene::MyScene(){
	// render text
	text = new Text("assets/arial.ttf", 1, glm::vec3(0,1,0));
	text->message = "QWERTYUIOPASDFGHJKLZXCVBNM!";
	text->setColorLerp(glm::vec3(1, 0, 0), glm::vec3(0, 0, 1));
	text->position.y = 100;
	this->addText(text);

	entitys = std::vector<MyEntity*>();
	for (int i = 0; i < 20; i++){
		entitys.push_back(new MyEntity());
		entitys[i]->sprite->loadTexture("assets/broodje.jpg", i, i);
		this->addChild(entitys[i]);
	}
}	

void MyScene::update(float deltatime) {
	for (int i = 0; i < entitys.size(); i++) {
		entitys[i]->update(deltatime);
	}
}

MyScene::~MyScene(){
}

