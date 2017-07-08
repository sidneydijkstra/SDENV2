#include "scene.h"

// TEMP meshes
Mesh* cube;

// scene constructor
Scene::Scene(Input* _input, Camera* _camera) {
	// set scene input and camera
	input = _input;
	camera = _camera;

	// add light
	addLight();
	light->position = glm::vec3(2, 2, 2);

	// set meshes
	cube = new Mesh();
	cube->loadMeshTexture("assets/gold.jpg");

	this->addChild(cube);


	cube->loadObject("assets/gokart.obj");

	// scene create message
	std::cout << "created new scene" << std::endl;
}

// scene update
void Scene::update(float deltatime){
	cube->rotation.y += 1 * deltatime;
}

// scene deconstructor
Scene::~Scene(){
	// remove childeren
	for each (Mesh* mesh in _childeren){
		delete mesh;
	}
}

