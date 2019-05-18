#include "sprite.h"

Sprite::Sprite(){
	// set texture to null
	_texturename = NULL;

	// declare filter and wrap
	_filter = 0;
	_wrap = 0;
}

Sprite::~Sprite(){
}

void Sprite::loadTexture(const char * location, int filter, int wrap){
	// set texture name
	_texturename = location;

	// set texture type, filter and wraping
	_filter = filter;
	_wrap = wrap;
}

void Sprite::loadTexture(const char * location) {
	this->loadTexture(location, 0, 0);
}

void Sprite::removeTexture(){
	_texturename = NULL;
}

