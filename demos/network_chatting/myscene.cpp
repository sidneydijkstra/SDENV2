#include "myscene.h"


MyScene::MyScene(){
	this->setSceneMode(SCENE2D); // <-- set scene mode

	_canvas = new Canvas();
	_message = new UIText("", 0.4, glm::vec3(1, 0, 0));
	_message->message = "temp message";
	_collection = new UICollection();
	_collection->position = glm::vec3(SWIDTH / 2, SHEIGHT / 2, 0);
	_collection->addUIText(_message);
	_canvas->addChild(_collection);
	this->addCanvas(_canvas);

	if (NetworkManager::getInstance()->init(IpAddress("127.0.0.1"), 8001)) {
		_message->message = "connected to server on IP: 127.0.0.1 PORT: 8001";
	}
	else {
		_message->message = "could not connect to server on IP: 127.0.0.1 PORT: 8001";
	}
}	

void MyScene::update(float deltatime) {
	_canvas->update();
}

MyScene::~MyScene(){
	delete _message;
	delete _collection;
	delete _canvas;
}

