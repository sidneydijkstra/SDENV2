#include "fontloader.h"

FontLoader::FontLoader(){
	// load normal font
	this->addFont("assets/arial.ttf");
}

FontLoader::~FontLoader(){
}

void FontLoader::addFont(const char * location){
	// freetype var
	FT_Library freetype;

	// init freetype
	if (FT_Init_FreeType(&freetype)){
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}else{
		std::cout << "FREETYPE: init freetype complete" << std::endl;
	}

	// load font file
	FT_Face face;
	if (FT_New_Face(freetype, location, 0, &face)){
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}else{
		std::cout << "FREETYPE: loaded freetype font" << std::endl;
	}

	// set font size
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

	// create temp chars list
	std::map<GLchar, Character> chars;
	for (GLubyte c = 0; c < 128; c++){ // Load first 128 characters of ASCII set
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// Now store character for later use
		Character ch = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		// add char to chars list
		chars.insert(std::pair<GLchar, Character>(c, ch));
	}

	// add new font to list of fonts
	std::cout << "added new font: " << location << std::endl;
	fonts.insert(std::pair<std::string, std::map<GLchar, Character>>(location, chars));

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy freetype and face when done
	FT_Done_Face(face);
	FT_Done_FreeType(freetype);
}

std::map<GLchar, Character> FontLoader::getFont(const char * location){
	auto search = fonts.find(location);
	if (search != fonts.end()) {
		return search->second;
	}else {
		for (int i = 0; i < unknown.size(); i++){
			if (unknown[i] == location) {
				return fonts.begin()->second;
			}
		}

		this->addFont(location);
		auto search = fonts.find(location);
		if (search != fonts.end()) {
			return search->second;
		}else {
			unknown.push_back(location);
			return fonts.begin()->second;
		}
	}
}
