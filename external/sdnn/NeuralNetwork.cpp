#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(int _input, int _hidden, int _output){
	this->_inputNodeSize = _input;
	this->_hiddenNodeSize = _hidden;
	this->_outputNodeSize = _output;

	this->_weightsIH = new Matrix(_hiddenNodeSize, _inputNodeSize);
	this->_weightsHO = new Matrix(_outputNodeSize, _hiddenNodeSize);

	this->_weightsIH->randomise();
	this->_weightsHO->randomise();

	this->_biasHidden = new Matrix(_hiddenNodeSize, 1);
	this->_biasOutput = new Matrix(_outputNodeSize, 1);

	this->_biasHidden->randomise();
	this->_biasOutput->randomise();

	this->_learningRait = 0.1f;
}

NeuralNetwork::~NeuralNetwork(){
	delete _weightsIH;
	delete _weightsHO;
	delete _biasHidden;
	delete _biasOutput;
}

std::vector<float> NeuralNetwork::predict(std::vector<float> _inputArray){
	// create input matrix
	Matrix* inputs = Matrix::fromVector(_inputArray);

	// generating hidden outputs
	Matrix* hidden = Matrix::dot(this->_weightsIH, inputs);
	hidden->add(this->_biasHidden);
	// activation function
	hidden = sigmoid(hidden);

	// generating hidden outputs
	Matrix* output = Matrix::dot(this->_weightsHO, hidden);
	output->add(this->_biasOutput);
	// activation function
	output = sigmoid(output);

	std::vector<float> awnser = output->toVector();
	delete inputs;
	delete hidden;
	delete output;

	return awnser;
}

void NeuralNetwork::train(std::vector<float> _inputArray, std::vector<float> _targetArray){
	// create input matrix
	Matrix* inputs = Matrix::fromVector(_inputArray);

	// generating hidden outputs
	Matrix* hidden = Matrix::dot(this->_weightsIH, inputs);
	hidden->add(this->_biasHidden);
	// activation function
	hidden = sigmoid(hidden);

	// generating hidden outputs
	Matrix* outputs = Matrix::dot(this->_weightsHO, hidden);
	outputs->add(this->_biasOutput);
	// activation function
	outputs = sigmoid(outputs);

	// get target in array
	Matrix* targets = Matrix::fromVector(_targetArray);

	// calculate output error
	Matrix* outputErrors = Matrix::sub(targets, outputs);

	// calculate output gradient
	Matrix* outputGradients = this->dsigmoid(outputs);
	outputGradients->mult(outputErrors);
	outputGradients->mult(this->_learningRait);

	// calculate hidden->output deltas
	Matrix* hiddenTranspose = Matrix::transpose(hidden);
	Matrix* weightHODeltas = Matrix::dot(outputGradients, hiddenTranspose);

	// adjust weights
	this->_weightsHO->add(weightHODeltas);
	this->_biasOutput->add(outputGradients);

	// Calculate the hidden layer errors
	Matrix* weightsHOTranspose = Matrix::transpose(this->_weightsHO);
	Matrix* hiddenErrors = Matrix::dot(weightsHOTranspose, outputErrors);

	//  Calculate hidden gradient
	Matrix* hiddenGradients = this->dsigmoid(hidden);
	hiddenGradients->mult(hiddenErrors);
	hiddenGradients->mult(this->_learningRait);

	// Calcuate input->hidden deltas
	Matrix* inputsTranspose = Matrix::transpose(inputs);
	Matrix* weightIHDeltas = Matrix::dot(hiddenGradients, inputsTranspose);

	// adjust weights
	this->_weightsIH->add(weightIHDeltas);
	this->_biasHidden->add(hiddenGradients);

	delete inputs;
	delete hidden;
	delete outputs;
	delete targets;
	delete outputErrors;
	delete outputGradients;
	delete hiddenTranspose;
	delete weightHODeltas;
	delete weightsHOTranspose;
	delete hiddenErrors;
	delete hiddenGradients;
	delete inputsTranspose;
	delete weightIHDeltas;
}

Matrix* NeuralNetwork::sigmoid(Matrix* _matrix){
	for (int i = 0; i < _matrix->rows; i++){
		for (int j = 0; j < _matrix->cols; j++){
			_matrix->data[i][j] = (1 / (1 + exp(-_matrix->data[i][j])));
		}
	}
	return _matrix;
}

Matrix* NeuralNetwork::dsigmoid(Matrix* _matrix){
	Matrix* result = new Matrix(_matrix->rows, _matrix->cols);
	for (int i = 0; i < _matrix->rows; i++) {
		for (int j = 0; j < _matrix->cols; j++) {
			result->data[i][j] = (_matrix->data[i][j] * (1 - _matrix->data[i][j]));
		}
	}
	return result;
}
