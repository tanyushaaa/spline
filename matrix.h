#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>

double det_(double **T, int N);

class Matrix {
public:
    Matrix(int n);
	Matrix(std::pair<double**, int> m);
	Matrix& operator= (Matrix&& m);
    bool main_diagonal() const;
    std::pair<double**, int> GetA() const;
    double determ() const;
	~Matrix();
	friend std::ostream& operator<< (std::ostream &out, const Matrix& matrix);
    double* operator[](int i);

private:
    int n_; //кол-во неизвестных
	double** A = nullptr;
	double det;
};

