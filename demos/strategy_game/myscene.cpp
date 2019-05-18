#include "myscene.h"


MyScene::MyScene(){
	_map = new Map();
	this->addChild(_map);
	_map->generateGrid();
}	

void MyScene::update(float deltatime) {
	this->camera()->move2D(deltatime, 50);
}

MyScene::~MyScene(){
	delete _map;
}

