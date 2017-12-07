
#include <core.h>
#include <sdenv2config.h>
#include "myscene.h"

#include <iostream>

// main function
int main() {
	// create the renderer and call its constructor
	Core* core = new Core();

	// create myscene and set it as current scene
	Scene* myscene = new MyScene();
	core->scenemanager->setCurrentScene(myscene);

	// call the run function
	while (core->run()) {
		// do something
	}

	// delete myscene
	delete myscene;

	// delete the renderer
	delete core;

	// rerurn 0
	return 0;
}
