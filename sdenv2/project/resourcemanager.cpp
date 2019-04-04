#include "resourcemanager.h"

Resourcemanager::Resourcemanager(){
	_textures = std::map<std::string, Texture*>();
}

Resourcemanager::~Resourcemanager(){
	std::map<std::string, Texture*>::iterator text_it;
	for (text_it = _textures.begin(); text_it != _textures.end(); ++text_it) {
		if (text_it->second != NULL) {
			//std::cout << text_it->first << " => " << text_it->second << '\n';
			delete text_it->second;
		}
	}
	_textures.clear();
}

GLuint Resourcemanager::getTexture(const char * location, int filter, int wrap){
	if (_textures[location] != NULL) {
		return _textures[location]->getTexture();
	}

	Texture* t = new Texture();
	t->loadTexture(location, filter, wrap);

	_textures[location] = t;

	return _textures[location]->getTexture();
}
