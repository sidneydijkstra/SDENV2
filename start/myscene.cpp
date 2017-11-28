#include "myscene.h"

Mesh* entity1;
Mesh* entity2;
Mesh* entity3;
Mesh* entity4;
Mesh* entity5;
Mesh* entity6;
Text* text;

Color col;

MyScene::MyScene(){
	col = Color();
	col.setColor(0,0,0);

	entity1 = new MyEntity();
	entity1->color = col;
	this->addChild(entity1);

	entity2 = new MyEntity();
	this->addChild(entity2);

	entity3 = new MyEntity();
	this->addChild(entity3);

	entity4 = new MyEntity(); // 2d view direction
	entity4->loadMeshTexture("assets/matthijs.png");
	this->addChild(entity4);

	entity5 = new MyEntity();
	this->addChild(entity5);

	entity6 = new MyEntity();
	this->addChild(entity6);

	this->addLight();
    this->getLight()->position = glm::vec3(0,3,0);
	entity6->position = glm::vec3(0, 3, 0);
	entity6->scale = glm::vec3(0.2f, 0.2f, 0.2f);

	entity1->position = glm::vec3(4, 0, 0);
	entity2->position = glm::vec3(-4, 0, 0);
	entity3->position = glm::vec3(0, 0, 4);
	entity4->position = glm::vec3(0, 0, -8);
	entity5->position = glm::vec3(0, 4, 0);

	text = new Text("assets/arial.ttf", 1, glm::vec3(0,1,0));
	text->message = "QWERTYUIOPASDFGHJKLZXCVBNM!";
	text->setColorLerp(glm::vec3(1, 0, 0), glm::vec3(0, 0, 1));
	text->position.y = 100;
	this->addText(text);


}	

MyScene::~MyScene(){
}

void MyScene::update(float deltatime){
	entity1->color = entity1->color.lerpColor(entity1->color, Color(255, 0, 255), 5 * deltatime);
}
