#include "leveleditor.h"

LevelEditor::LevelEditor()
{
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::update(float deltatime){
	if (input()->getKey(GLFW_KEY_W)) {
		camera()->position.y += 4 * deltatime;
	}
	if (input()->getKey(GLFW_KEY_S)) {
		camera()->position.y -= 4 * deltatime;
	}

	if (input()->getKey(GLFW_KEY_D)) {
		camera()->position.x += 4 * deltatime;
	}
	if (input()->getKey(GLFW_KEY_A)) {
		camera()->position.x -= 4 * deltatime;
	}
}
