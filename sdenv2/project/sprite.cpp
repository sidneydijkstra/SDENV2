#include "sprite.h"

Sprite::Sprite(){
	// set texture to null
	_texture = NULL;

	// declare type
	_type = 0;

	// declare width and height
	width = 0;
	height = 0;

	// declare filter and wrap
	_filter = 0;
	_wrap = 0;
}

Sprite::~Sprite(){
}

void Sprite::loadTexture(const char * location, int filter, int wrap){
	// set texture type, filter and wraping
	_type = 0;
	_filter = filter;
	_wrap = wrap;

	// bind texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// load texture
	int _width, _height;
	unsigned char* image = SOIL_load_image(location, &_width, &_height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	width = _width;
	height = _height;

	// filter the Texture
	if (filter <= 0 || filter > 3) {
		// No filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	} else if (filter == 1) {
		// Linear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	} else if (filter == 2) {
		// Bilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else if (filter == 3) {
		// Trilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	if (wrap <= 0 || wrap > 2) {
		// wrap GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (wrap == 1) {
		// wrap GL_MIRRORED_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}
	else if (wrap == 2) {
		// wrap GL_CLAMP_TO_EDGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	
	// free image from soil and unbind image
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set texture
	_texture = texture;
}


void Sprite::loadSpriteSheet(const char * location, int rows, int cells, int filter, int wrap){
	// load texture
	this->loadTexture(location, filter, wrap);

	// set type
	_type = 1;

	// set texture cords
	float xAmount = 1 / float(rows);
	float yAmount = 1 / float(cells);

	std::cout << xAmount << std::endl;

	for (int y = 0; y < rows; y++){
		for (int x = 0; x < cells; x++) {

			std::vector<glm::vec2> spr;
			glm::vec2 cords;

			// top-left
			cords.x = x * xAmount;
			cords.y = 1 - (y * yAmount);
			spr.push_back(cords);

			// bottom-left
			cords.x = x * xAmount;
			cords.y = 1 - ((y + 1) * yAmount);
			spr.push_back(cords);

			// bottom-right
			cords.x = (x + 1) * xAmount;
			cords.y = 1 - ((y + 1) * yAmount);
			spr.push_back(cords);

			// top-right
			cords.x = (x + 1) * xAmount;
			cords.y = 1 - (y * yAmount);
			spr.push_back(cords);
			
			/*
			for (int i = 0; i < spr.size(); i++){ // TEMP print values
				std::cout << " [ x: " << spr[i].x << " , y: " << spr[i].y << " ] ";
			}
			std::cout << std::endl;
			*/

			_spriteSheetCords.push_back(spr);
		}
	}
}
