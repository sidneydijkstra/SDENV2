#include "maze.h"

Maze::Maze(){
	this->setSceneMode(SCENE2D);

	worldsize = 20;

	genStack = std::stack<Cell*>();
	isSolved = false;
	isDone = false;

	// create grid
	for (int y = 0; y < worldsize; y++) {
		std::vector<Cell*> cells;
		for (int x = 0; x < worldsize; x++) {
			cells.push_back(new Cell(x,y, SWIDTH/worldsize));
			this->addChild(cells[x]);
		}
		grid.push_back(cells);
	}

	int i = 0;
	std::cout << "Enter seed: ";
	std::cin >> i;
	std::srand(i);

	// set current cell
	currentcell = grid[0][0];
	currentcell->inside();
	genStack.push(currentcell);
}

void Maze::update(float deltatime) {
	if (!isSolved){
		generateMaze();
	}else if (!isDone) {
		solveMaze();
	}
	/*else {
		int i = 0;
		std::cout << "Enter seed: ";
		std::cin >> i;
		std::srand(i);

		for (int y = 0; y < worldsize; y++) {
			for (int x = 0; x < worldsize; x++) {
				grid[y][x]->disable();
				grid[y][x]->scale = glm::vec3(SWIDTH/worldsize, SHEIGHT/worldsize, 0);

			}
		}
		serStack.clear();
		path.clear();
	}*/
}

void Maze::generateMaze(){
	// get neighbours of current cell
	std::vector<Cell*> neighbours = this->getNeighbours(currentcell);
	if (neighbours.size() > 0) {
		int i = rand() % neighbours.size();
		// set viseted true to current tile
		currentcell->enable();
		currentcell->visited = true;

		// open walls
		currentcell->closeWall(neighbours[i]);

		// set new visited
		currentcell = neighbours[i];
		currentcell->inside();

		// add new current cell to the generate stack
		genStack.push(currentcell);
	}
	else {
		// if current cell is not the end
		if (currentcell != grid[0][0]) {
			// set current cell visited
			currentcell->visited = true;
			// set current cell to enable
			currentcell->enable();
			// pop the stack
			genStack.pop();
			// set new current cell
			currentcell = genStack.top();
			currentcell->inside();
		}
		else {
			// set maze solved to true
			isSolved = true;
			// set new current cell
			currentcell = grid[0][0];

			serStack.push_back(currentcell); // remove

			// reset map to be clean again
			for (int y = 0; y < worldsize; y++){
				for (int x = 0; x < worldsize; x++){
					grid[y][x]->visited = false;
				}
			}
			
			// clean genstack
			while (!genStack.empty()) {
				genStack.pop();
			}

			currentcell->visited = true; // remove
		}
	}
}

void Maze::solveMaze(){
	// create temp stack
	std::vector<Cell*> tempStack;
	for (int i = 0; i < serStack.size(); i++) {
		// get current cell
		Cell* cell = serStack[i];
		cell->inside();

		// get current cell neighbours he can move to
		std::vector<Cell*> n = this->getNeighboursSolve(cell);
		for (int y = 0; y < n.size(); y++) {
			// add new cell to temp stack, set parent and set visited true
			n[y]->parent = cell;
			n[y]->visited = true;
			tempStack.push_back(n[y]);

			// check if at end
			if (n[y] == grid[worldsize - 1][worldsize - 1]) {

				// first clean map
				for (int y = 0; y < worldsize; y++){
					for (int x = 0; x < worldsize; x++){
						grid[y][x]->enable();
					}
				}

				// get end cell
				Cell* p = n[y];
				// get parent from end cell and then parent from parent till you at the end
				while (p != NULL) {
					path.push_back(p);
					p->scale = glm::vec3((SWIDTH / worldsize) / 4, (SHEIGHT / worldsize) / 4, 0);
					p->path();
					p = p->parent;
				}

				this->isDone = true;

				grid[0][0]->disable();
				grid[worldsize-1][worldsize-1]->inside();

				return;
			}
		}
	}
	serStack = tempStack;
}

std::vector<Cell*> Maze::getNeighbours(Cell * c) {
	std::vector<Cell*> neighbours;

	int x = c->gridX;
	int y = c->gridY;

	if (y + 1 < grid.size() && !grid[y + 1][x]->visited) { // get top
		neighbours.push_back(grid[y + 1][x]);
	}
	if (y - 1 >= 0 && !grid[y - 1][x]->visited) { // get bottom
		neighbours.push_back(grid[y - 1][x]);
	}
	if (x - 1 >= 0 && !grid[y][x - 1]->visited) { // get left
		neighbours.push_back(grid[y][x - 1]);
	}
	if (x + 1 < grid[y].size() && !grid[y][x + 1]->visited) { // get right
		neighbours.push_back(grid[y][x + 1]);
	}

	return neighbours;
}

std::vector<Cell*> Maze::getNeighboursSolve(Cell * c){
	std::vector<Cell*> neighbours;

	int x = c->gridX;
	int y = c->gridY;

	if (y + 1 < grid.size() && !grid[y + 1][x]->visited && 
		!c->wallTop->active && !grid[y + 1][x]->wallBottom->active) { // get top
		neighbours.push_back(grid[y + 1][x]);
	}
	if (y - 1 >= 0 && !grid[y - 1][x]->visited && 
		!c->wallBottom->active && !grid[y - 1][x]->wallTop->active) { // get bottom
		neighbours.push_back(grid[y - 1][x]);
	}
	if (x - 1 >= 0 && !grid[y][x - 1]->visited && 
		!c->wallLeft->active && !grid[y][x - 1]->wallRight->active) { // get left
		neighbours.push_back(grid[y][x - 1]);
	}
	if (x + 1 < grid[y].size() && !grid[y][x + 1]->visited &&
		!c->wallRight->active && !grid[y][x + 1]->wallLeft->active) { // get right
		neighbours.push_back(grid[y][x + 1]);
	}

	return neighbours;
}

Maze::~Maze(){
}


