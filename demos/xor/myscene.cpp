#include "myscene.h"


MyScene::MyScene(){ // windows size: 800/800
	_map = std::vector<std::vector<Tile*>>();

	// create map
	int tileSize = 40; 
	loopLenght = 800 / 40;
	for (int i = 0; i < loopLenght; i++){
		std::vector<Tile*> tempList = std::vector<Tile*>();
		for (int j = 0; j < loopLenght; j++){
			Tile* tempTile = new Tile(tileSize / 2 + (tileSize*i), tileSize / 2 + (tileSize*j), tileSize/2, tileSize/2);
			tempList.push_back(tempTile);
			this->addChild(tempTile);
		}
		_map.push_back(tempList);
	}

	// create neuralnetwork
	nn = new NeuralNetwork(2, 2, 1);
}	

void MyScene::update(float deltatime) {
	//this->camera()->move2D(deltatime, 100);

	// train neuralnetwork
	for (int i = 0; i < 50; i++) {
		int r = rand() % 4;
		nn->train(data[r].input, data[r].output);
	}

	for (int i = 0; i < loopLenght; i++) {
		for (int j = 0; j < loopLenght; j++) {
			Tile* tempTile = _map[i][j];
			std::vector<float> values = Data::fill(map(tempTile->position.x, 0, 800, 0.0f, 1.0f), map(tempTile->position.y, 0, 800, 0.0f, 1.0f));
			float guess = nn->predict(values)[0];
			int c = guess * 255;
			tempTile->color = Color(c, c, c);
		}
	}
}

float MyScene::map(float _value, float _mina, float _maxa, float _minb, float _maxb){ // TODO: funtion not working like a real map function (this is just a fast fix)
	return (_value / _maxa) * _maxb;
}

MyScene::~MyScene(){
	delete nn;
}

