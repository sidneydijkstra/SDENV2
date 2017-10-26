#include "myscene.h"

Mesh* entity;

MyScene::MyScene(){
	entity = new MyEntity();
	this->addChild(entity);

	this->addLight();
	this->getLight()->position = glm::vec3(4, 8, 0);
}

MyScene::~MyScene(){
	delete entity;
}

void MyScene::update(float deltatime){
	entity->rotation.x += 1 * deltatime;
}
