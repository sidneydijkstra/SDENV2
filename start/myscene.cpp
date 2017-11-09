#include "myscene.h"

Mesh* entity1;
Mesh* entity2;
Mesh* entity3;
Mesh* entity4;
Mesh* entity5;
Mesh* entity6;

MyScene::MyScene(){
	entity1 = new MyEntity();
	this->addChild(entity1);

	entity2 = new MyEntity();
	this->addChild(entity2);

	entity3 = new MyEntity();
	this->addChild(entity3);

	entity4 = new MyEntity(); // 2d view direction
	this->addChild(entity4);

	entity5 = new MyEntity();
	this->addChild(entity5);

	entity6 = new MyEntity();
	this->addChild(entity6);

	this->addLight();
    this->getLight()->position = glm::vec3(0,3,0);
	this->getLight()->lightColor = glm::vec3(2,0,1);
	entity6->position = glm::vec3(0, 3, 0);
	entity6->scale = glm::vec3(0.2f, 0.2f, 0.2f);

	entity1->position = glm::vec3(4, 0, 0);
	entity2->position = glm::vec3(-4, 0, 0);
	entity3->position = glm::vec3(0, 0, 4);
	entity4->position = glm::vec3(0, 0, -4);
	entity5->position = glm::vec3(0, 4, 0);

	for (int i = 0; i < this->getChildCount(); i++){
		this->getChilderen()[i]->color = glm::vec3(i * 0.2f, i * 0.4f, i * 0.15f);
	}

	entity4->scale = glm::vec3(3,3,1);

}	

MyScene::~MyScene(){
}

void MyScene::update(float deltatime){
}
