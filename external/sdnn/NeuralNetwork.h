#pragma once

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "matrix.h"
#include <math.h>

class NeuralNetwork{
public:
	NeuralNetwork(int _input, int _hidden, int _output);
	~NeuralNetwork();

	std::vector<float> predict(std::vector<float> _inputArray);
	void train(std::vector<float> _inputArray, std::vector<float> _targetArray);

	// activation functions
	Matrix* sigmoid(Matrix* _matrix);
	Matrix* dsigmoid(Matrix* _matrix);

private:

	int _inputNodeSize;
	int _hiddenNodeSize;
	int _outputNodeSize;

	Matrix* _weightsIH;
	Matrix* _weightsHO;

	Matrix* _biasHidden;
	Matrix* _biasOutput;

	float _learningRait;
};

class Data {
public:
	Data() {};
	Data(std::vector<float> _input, std::vector<float> _output) {
		input = _input;
		output = _output;
	};

	std::vector<float> input;
	std::vector<float> output;

	static std::vector<float> fill(float _a) {
		std::vector<float> result = std::vector<float>();
		result.push_back(_a);
		return result;
	}
	static std::vector<float> fill(float _a, float _b) {
		std::vector<float> result = std::vector<float>();
		result.push_back(_a);
		result.push_back(_b);
		return result;
	}
};

#endif /* end NEURALNETWORK_H */