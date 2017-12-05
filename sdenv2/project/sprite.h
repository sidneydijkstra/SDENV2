#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// include glew
#include <GL/glew.h>
// include soil
#include <SOIL.h>



class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	// load texture
	void loadTexture(const char* location, int filter, int wrap);

	// load texture from sprite sheet
	void loadSpriteSheet(const char* location,int rows, int cells, int filter, int wrap); // NOT WORKING YET!

	// get texture
	GLuint getTexture() { return _texture; };
	// get if sprite is spritesheet
	bool isSpriteSheet() { if (_type == 1) return true; return false; }
	// get filter type
	int filter() { return _filter; }
	// get wraping type 
	int wraping() { return _wrap; }

	// texture width and height
	int width;
	int height;

private:
	// texture info
	GLuint _texture;
	std::vector<std::vector<glm::vec2>> _spriteSheetCords; // top-right, bottom-right, bottom-left, top-left

	// texture type
	// 0 = normal
	// 1 = sprite sheet
	int _type;

	// filter and wrap
	int _filter;
	int _wrap;
};

#endif /* end SPRITE_H */
