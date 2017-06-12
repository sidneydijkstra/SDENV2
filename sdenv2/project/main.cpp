
#include "renderer.h"

#include <iostream>

// main function
int main() {
	// create the renderer and call its constructor
	Renderer* renderer = new Renderer();

	// call the run function
	renderer->run();

	// delete the renderer
	delete renderer;

	// rerurn 0
	return 0;
}
