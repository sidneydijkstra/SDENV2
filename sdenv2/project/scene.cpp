#include "scene.h"

// TEMP meshes
Mesh* cube;

// scene constructor
Scene::Scene(Input* _input, Camera* _camera) {
	// set scene input and camera
	input = _input;
	camera = _camera;

	// set meshes
	cube = new Mesh();
	cube->loadMeshTexture("assets/timmy.jpg");

	this->addChild(cube);

	// scene create message
	std::cout << "created new scene" << std::endl;
}

// scene update
void Scene::update(float deltatime){
	cube->rotation.x += 1 * deltatime;
}

// scene deconstructor
Scene::~Scene(){
	// remove childeren
	for each (Mesh* mesh in _childeren){
		delete mesh;
	}
}

