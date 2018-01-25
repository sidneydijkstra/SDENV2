
#include <core.h>
#include <sdenv2config.h>
#include "myscene.h"
#include "leveleditor.h"

#include <iostream>

// main function
int main() {
	// create the renderer and call its constructor
	Core* core = new Core();

	// create myscene and set it as current scene
	Scene* myscene = new MyScene();
	core->scenemanager->setCurrentScene(myscene);

	// create level editor and set it as current scene
	Scene* leveleditor = new LevelEditor();
	core->scenemanager->addCurrentScene(leveleditor);

	//myscene->NEXT();

	// call the run function
	while (core->run()) {
		// do something
	}

	// delete myscene and level editor
	delete myscene;
	delete leveleditor;

	// delete the renderer
	delete core;

	// rerurn 0
	return 0;
}
