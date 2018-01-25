#include "editorcanvas.h"

EditorCanvas::EditorCanvas(){
	_textTile = new UITextField("message", "");
	_textTile->position = glm::vec3(SWIDTH - 100, SHEIGHT-20, 0);
	this->addChild(_textTile);

	_textmode = new UITextField("message", "");
	_textmode->position = glm::vec3(SWIDTH - 100, SHEIGHT - 40, 0);
	this->addChild(_textmode);

	_textlayer = new UITextField("message", "");
	_textlayer->position = glm::vec3(SWIDTH - 100, SHEIGHT - 60, 0);
	this->addChild(_textlayer);
}

EditorCanvas::~EditorCanvas(){
	delete _textTile;
}

void EditorCanvas::update(float deltatime)
{
}

void EditorCanvas::addTileNameText(std::string message){
	this->_textTile->text()->message = message;
}

void EditorCanvas::addModeText(std::string message){
	this->_textmode->text()->message = message;
}

void EditorCanvas::addLayerText(std::string message){
	this->_textlayer->text()->message = message;
}
