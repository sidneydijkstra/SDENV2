
#include <core.h>
#include "world.h"

#include <iostream>

// main function
int main() {
	// create the renderer and call its constructor
	Core* core = new Core();

	// create myscene and set it as current scene
	World* myscene = new World();
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
