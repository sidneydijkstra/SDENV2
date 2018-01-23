#include "canvas.h"

Canvas::Canvas(){
	this->active = true;
}

Canvas::~Canvas(){
}

void Canvas::update(){
}

void Canvas::addChild(UICollection * child){
	_childeren.push_back(child);
}

void Canvas::removeChild(UICollection * child){
	for (int i = 0; i < _childeren.size(); i++) {
		if (_childeren[i] == child) {
			_childeren.erase(_childeren.begin() + i);
			break;
		}
	}
}

std::vector<UICollection*> Canvas::getAllChilderen(){
	return _childeren;
}

int Canvas::getChildCount(){
	return _childeren.size();
}
