#include <string>
#include <iostream>

#include "matrix.h"

Matrix::Matrix(int _rows, int _cols){
	this->rows = _rows;
	this->cols = _cols;

	 this->data = std::vector<std::vector<float>>();

	for (int r = 0; r < _rows; r++){
		std::vector<float> col = std::vector<float>();
		for (int c = 0; c < _cols; c++){
			col.push_back(0.0f);
		}
		data.push_back(col);
	}
}

Matrix::Matrix(){
	this->rows = 0;
	this->cols = 0;

	this->data = std::vector<std::vector<float>>();
}

Matrix::~Matrix() {
	data.clear();
}

void Matrix::add(Matrix * _matrix){
	if (_matrix->rows != this->rows || _matrix->cols != this->cols) {
		std::cout << "You can't add two matrix's if there rows/cols are not the same" << std::endl;
		return;
	}

	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			this->data[r][c] = this->data[r][c] + _matrix->data[r][c];
		}
	}
}

void Matrix::add(float _value){
	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			this->data[r][c] += _value;
		}
	}
}

void Matrix::mult(Matrix * _matrix) {
	if (_matrix->rows != this->rows || _matrix->cols != this->cols) {
		std::cout << "You can't mult two matrix's if there rows/cols are not the same" << std::endl;
		return;
	}

	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			this->data[r][c] = this->data[r][c] * _matrix->data[r][c];
		}
	}
}

void Matrix::mult(float _value){
	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			this->data[r][c] *= _value;
		}
	}
}

void Matrix::sub(Matrix * _matrix) {
	if (_matrix->rows != this->rows || _matrix->cols != this->cols) {
		std::cout << "You can't sub two matrix's if there rows/cols are not the same" << std::endl;
		return;
	}

	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			this->data[r][c] = this->data[r][c] - _matrix->data[r][c];
		}
	}
}

void Matrix::sub(float _value){
	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			this->data[r][c] -= _value;
		}
	}
}

void Matrix::dot(Matrix * _matrix){
	if (_matrix->rows != this->cols || _matrix->cols != this->rows) {
		std::cout << "You can't dot two matrix's if there rows/cols are the same" << std::endl;
		return;
	}

	Matrix* result = new Matrix(this->rows, _matrix->cols);

	for (int r = 0; r < result->rows; r++) {
		for (int c = 0; c < result->cols; c++) {
			float sum = 0.0f;

			for (int k = 0; k < this->cols; k++){
				sum += this->data[r][k] * _matrix->data[k][c];
			}

			result->data[r][c] = sum;
		}
	}

	this->copy(result);
	delete result;
}

Matrix* Matrix::add(Matrix * _matrixA, Matrix * _matrixB){
	if (_matrixA->rows != _matrixB->rows || _matrixA->cols != _matrixB->cols) {
		std::cout << "You can't add two matrix's if there rows/cols are not the same" << std::endl;
		return nullptr;
	}

	Matrix* result = new Matrix(_matrixA->rows, _matrixA->cols);

	for (int r = 0; r < _matrixA->rows; r++) {
		for (int c = 0; c < _matrixA->cols; c++) {
			result->data[r][c] = _matrixA->data[r][c] + _matrixB->data[r][c];
		}
	}

	return result;
}

Matrix* Matrix::mult(Matrix * _matrixA, Matrix * _matrixB){
	if (_matrixA->rows != _matrixB->rows || _matrixA->cols != _matrixB->cols) {
		std::cout << "You can't mult two matrix's if there rows/cols are not the same" << std::endl;
		return nullptr;
	}

	Matrix* result = new Matrix(_matrixA->rows, _matrixA->cols);

	for (int r = 0; r < _matrixA->rows; r++) {
		for (int c = 0; c < _matrixA->cols; c++) {
			result->data[r][c] = _matrixA->data[r][c] * _matrixB->data[r][c];
		}
	}

	return result;
}

Matrix* Matrix::sub(Matrix * _matrixA, Matrix * _matrixB){
	if (_matrixA->rows != _matrixB->rows || _matrixA->cols != _matrixB->cols) {
		std::cout << "You can't sub two matrix's if there rows/cols are not the same" << std::endl;
		return nullptr;
	}

	Matrix* result = new Matrix(_matrixA->rows, _matrixA->cols);

	for (int r = 0; r < _matrixA->rows; r++) {
		for (int c = 0; c < _matrixA->cols; c++) {
			result->data[r][c] = _matrixA->data[r][c] - _matrixB->data[r][c];
		}
	}

	return result;
}

Matrix* Matrix::dot(Matrix * _matrixA, Matrix * _matrixB){
	if (_matrixA->cols != _matrixB->rows) {
		std::cout << "You can't dot two matrix's if there rows/cols are the same" << std::endl;
		return nullptr;
	}

	Matrix* result = new Matrix(_matrixA->rows, _matrixB->cols);

	for (int r = 0; r < result->rows; r++) {
		for (int c = 0; c < result->cols; c++) {
			float sum = 0.0f;

			for (int k = 0; k < _matrixA->cols; k++) {
				sum += _matrixA->data[r][k] * _matrixB->data[k][c];
			}

			result->data[r][c] = sum;
		}
	}

	return result;
}

Matrix * Matrix::transpose(Matrix * _matrix){
	Matrix* result = new Matrix(_matrix->cols, _matrix->rows);

	for (int i = 0; i < _matrix->rows; i++) {
		for (int j = 0; j < _matrix->cols; j++) {
			result->data[j][i] = _matrix->data[i][j];
		}
	}

	return result;
}

void Matrix::transpose(){
	Matrix* result = new Matrix(this->cols, this->rows);

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			result->data[j][i] = this->data[i][j];
		}
	}

	this->copy(result);
	delete result;
}

void Matrix::copy(Matrix * _matrix){
	this->rows = _matrix->rows;
	this->cols = _matrix->cols;
	this->data = _matrix->data;
}

void Matrix::randomise(){
	for (int r = 0; r < this->rows; r++) {
		for (int c = 0; c < this->cols; c++) {
			this->data[r][c] = rand() % 2 - 1;
		}
	}
}

void Matrix::print(){
	for (int r = 0; r < this->rows; r++) {
		std::cout << "[ ";
		for (int c = 0; c < this->cols; c++) {
			std::cout << std::to_string(this->data[r][c]);

			if (c < this->cols-1) {
				std::cout << ", ";
			}
		}
		std::cout << " ]" << std::endl;
	}
	std::cout << "" << std::endl;
}

Matrix* Matrix::fromVector(std::vector<float> _array){
	Matrix* result = new Matrix(_array.size(), 1);

	for (int c = 0; c < result->rows; c++){
		result->data[c][0] = _array[c];
	}

	return result;
}

std::vector<float> Matrix::toVector(){
	std::vector<float> result = std::vector<float>();

	for (int c = 0; c < this->cols; c++) {
		result.push_back(this->data[c][0]);
	}

	return result;
}
