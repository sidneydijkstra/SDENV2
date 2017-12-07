
#include <renderer.h>
#include <sdenv2config.h>
#include "myscene.h"

#include <iostream>

// main function
int main() {
	// create the renderer and call its constructor
	Renderer* renderer = new Renderer();

	// create myscene and set it as current scene
	Scene* myscene = new MyScene();
	renderer->scenemanager->setCurrentScene(myscene);

	// call the run function
	while (renderer->run()) {
		// do something
	}

	// delete myscene
	delete myscene;

	// delete the renderer
	delete renderer;

	// rerurn 0
	return 0;
}
