
#include <core.h>
#include <sdenv2config.h>

#include <iostream>
#include "myscene.h"

// main function
int main() {
	Core* core = new Core();
	MyScene* scene = new MyScene();
	core->scenemanager->setCurrentScene(scene);

	// call the run function
	while (core->run()) {
	}

	delete scene;
	delete core;

	return 0;
}
