
#include "renderer.h"

// devine functions
#define SWIDTH 800;
#define SHEIGHT 600;

// main function
int main() {
	int screenWidth = SWIDTH;
	int screenHeight = SWIDTH;
	// create renderer
	Renderer* renderer = new Renderer();
	// create window
	renderer->createWindow(screenWidth, screenHeight);

	// run main game loop
	renderer->run();

	// deletet renderer
	delete renderer;

	// stop program
	glfwTerminate();
	return 0;
}
