#include "particalsystem.h"

// ParticalSystem constructor
ParticalSystem::ParticalSystem(){
}

void ParticalSystem::update(float deltatime){
	if (_particals.size() < 120 && _lastSpawnedTime <= glfwGetTime()) {
		Partical* partical = new Partical(4);
		partical->getMesh()->position = this->position;
		_particals.push_back(partical);
		_lastSpawnedTime = glfwGetTime() + 0.2f;
	}

	for (size_t i = 0; i < _particals.size(); i++){
		_particals[i]->update(deltatime);

		// check if destroy partical
		if (_particals[i]->getLifeTime() <= glfwGetTime()) {
			Partical* _par = _particals[i];
			_particals.erase(_particals.begin() + i);
			delete _par;
		}
	}
}

std::vector<Mesh*> ParticalSystem::getAllParticalsMesh(){
	std::vector<Mesh*> _meshes;
	for (size_t i = 0; i < _particals.size(); i++){
		_meshes.push_back(_particals[i]->getMesh());
	}
	return _meshes;
}

// ParticalSystem deconstructor
ParticalSystem::~ParticalSystem(){
	for (size_t i = 0; i < _particals.size(); i++){
		delete _particals[i];
	}
}

