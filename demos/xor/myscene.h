#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H

#include <scene.h>
#include <mesh.h>
#include <timer.h>
#include <networkhandler.h>
#include <package.h>
#include <action.h>

#include <NeuralNetwork.h>
#include "tile.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);
private:
	float map(float _value, float _mina, float _maxa, float _minb, float _maxb);

	int loopLenght;
	std::vector<std::vector<Tile*>> _map;
	NeuralNetwork* nn;
	Data data[4] = {
		Data(Data::fill(1.0f, 1.0f), Data::fill(1.0f)),
		Data(Data::fill(0.0f, 0.0f), Data::fill(1.0f)),
		Data(Data::fill(1.0f, 0.0f), Data::fill(0.0f)),
		Data(Data::fill(0.0f, 1.0f), Data::fill(0.0f))
	};
};

#endif /* end MYSCENE_H */
