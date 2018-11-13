
#include <core.h>
#include <sdenv2config.h>
#include "leveleditor.h"

#include "levela.h"

#include <iostream>

// main function
int main() {
	// create the renderer and call its constructor
	Core* core = new Core();

	// create myscene and set it as current scene
	Scene* level_1 = new LevelA();
	core->scenemanager->setCurrentScene(level_1);

	// create level editor and set it as current scene
	//Scene* leveleditor = new LevelEditor();
	//core->scenemanager->addCurrentScene(leveleditor);

	//level_1->NEXT();

	// call the run function
	while (core->run()) {
		// do something
	}

	// delete myscene and level editor
	delete level_1;
	//delete leveleditor;

	// delete the renderer
	delete core;

	// rerurn 0
	return 0;
}
