#include "scene.h"

// TEMP meshes
Mesh* ground;
Mesh* cube;
Mesh* lightObject;

// scene constructor
Scene::Scene(Input* _input, Camera* _camera) {
	// set scene input and camera
	input = _input;
	camera = _camera;

	// add light
	addLight();
	light->position = glm::vec3(4,8,0);
	lightObject = new Mesh();
	lightObject->position = glm::vec3(4, 8, 0);

	// set meshes
	ground = new Mesh();
	ground->scale = glm::vec3(30,0.5f,30);
	ground->loadMeshTexture("assets/wood.jpg");


	cube = new Mesh();
	cube->position = glm::vec3(1.5f,3,0);
	cube->scale = glm::vec3(2, 2, 2);
	cube->loadMeshTexture("assets/wood.jpg");


	this->addChild(ground);
	this->addChild(cube);
	this->addChild(lightObject);

	// scene create message
	std::cout << "created new scene" << std::endl;
}

// scene update
void Scene::update(float deltatime){
	//cube->rotation.y += 1 * deltatime;
}

// scene deconstructor
Scene::~Scene(){
	// remove childeren
	for each (Mesh* mesh in _childeren){
		delete mesh;
	}
}

