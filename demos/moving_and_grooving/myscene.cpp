#include "myscene.h"


MyScene::MyScene(){
	this->setSceneMode(SCENE2D); // <-- set scene mode
	points = std::vector<Entity*>();

	player = new Collision();
	player->mesh()->loadQuad();
	player->position = glm::vec3(500, 500, 0);
	player->size = glm::vec3(20, 20, 0);
	player->color = Color(0, 100, 0);

	cube = new Collision();
	cube->mesh()->loadQuad();
	cube->position = glm::vec3(200, 200, 0);
	cube->size = glm::vec3(50, 50, 0);
	cube->_isStatic = true;

	this->addChild(player);
	this->addChild(cube);

	Entity* ctp = new Entity();
	ctp->mesh()->loadQuad();
	ctp->size = glm::vec3(5, 5, 0);
	ctp->color = Color(0, 0, 255);
	this->addChild(ctp);

	Entity* ptc = new Entity();
	ptc->mesh()->loadQuad();
	ptc->size = glm::vec3(5, 5, 0);
	ptc->color = Color(255, 0, 0);
	this->addChild(ptc);

	Entity* bpp = new Entity();
	bpp->mesh()->loadQuad();
	bpp->size = glm::vec3(5, 5, 0);
	bpp->color = Color(120, 120, 40);
	this->addChild(bpp);


	points.push_back(ptc);
	points.push_back(ctp);
	points.push_back(bpp);

}	

void MyScene::update(float deltatime) {
	int speed = 2;
	if (Input::getInstance()->getKey(GLFW_KEY_D)) {
		player->position.x += speed;
	}
	if (Input::getInstance()->getKey(GLFW_KEY_A)) {
		player->position.x -= speed;
	}
	if (Input::getInstance()->getKey(GLFW_KEY_S)) {
		player->position.y -= speed;
	}
	if (Input::getInstance()->getKey(GLFW_KEY_W)) {
		player->position.y += speed;
	}

	points[0]->position = player->getPointToBoarder(cube);
	points[1]->position = cube->getPointToBoarder(player);

	if(player->collision(cube)){
		//points[2]->position = player->getBoarderPlacementPoint(cube);
		player->position = player->getBoarderPlacementPoint(cube);
	}
	//player->collide(cube);
}

MyScene::~MyScene(){
	delete cube;
}

