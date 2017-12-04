#include "myscene.h"

Text* text;

MyScene::MyScene(){
	// render text
	text = new Text("assets/arial.ttf", 1, glm::vec3(0,1,0));
	text->message = "QWERTYUIOPASDFGHJKLZXCVBNM!";
	text->setColorLerp(glm::vec3(1, 0, 0), glm::vec3(0, 0, 1));
	text->position.y = 100;
	this->addText(text);

	entitys = std::vector<MyEntity*>();
	for (int i = 0; i < 10000; i++){
		entitys.push_back(new MyEntity());
		this->addChild(entitys[i]);
	}
}	

MyScene::~MyScene(){
}

void MyScene::update(float deltatime) {
	for (int i = 0; i < entitys.size(); i++) {
		entitys[i]->update(deltatime);
	}
}
