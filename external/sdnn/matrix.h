#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix{
public:
	Matrix(int _rows, int _cols);
	Matrix();
	~Matrix();

	void add(Matrix* _matrix);
	void add(float _value);
	void mult(Matrix* _matrix);
	void mult(float _value);
	void sub(Matrix* _matrix);
	void sub(float _value);
	void dot(Matrix* _matrix);

	static Matrix* add(Matrix* _matrixA, Matrix* _matrixB);
	static Matrix* mult(Matrix* _matrixA, Matrix* _matrixB);
	static Matrix* sub(Matrix* _matrixA, Matrix* _matrixB);
	static Matrix* dot(Matrix* _matrixA, Matrix* _matrixB);

	static Matrix* transpose(Matrix* _matrix);

	void transpose();
	void copy(Matrix* _matrix);
	void randomise();
	void print();

	static Matrix* fromVector(std::vector<float> _array);
	std::vector<float> toVector();

	int rows;
	int cols;

	std::vector<std::vector<float>> data;

private:
};

#endif /* end MATRIX_H */
