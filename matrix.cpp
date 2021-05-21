#include "matrix.h"

double det_(double** T, int N) {
	switch (N){
	case 1:
		return T[0][0];
	case 2:
		return T[0][0] * T[1][1] - T[0][1] * T[1][0];
	default:
		if (N < 1) {
			throw std::invalid_argument("There is no elements in this matrix.");
		}
		double **minor = new double*[N-1];		//массив указателей на столбцы исходной матрицы
		double det = 0;							//исключа€ заданные стр. и стл. (минор)
		int sign = 1;							//знак минора
		for (int i = 0; i < N; i++) {			//разложение по первому столбцу
			int sub_j = 0;
			for (int j = 0; j < N; j++) {		//заполнение "минорной" матрицы ссылками на исходные столбцы
				if (i != j)						//исключить i строку
					minor[sub_j++] = T[j] + 1;	//исключить 1й(0й) столбец
			}
			det += sign * T[i][0] * det_(minor, N-1);
			sign = -sign;
		}
		delete[] minor;
		return det;
	}
}

Matrix::Matrix(int n) : n_(n) {
    A = new double* [n_];
    for (int i = 0; i < n_; i++) {
        A[i] = new double [n_ + 1];
    }

    for(int i = 0; i < n_; i++){
        for(int j = 0; j < n_ + 1; j++){
            A[i][j] = 0.;
        }
    }

    det = 0.;
}

Matrix::Matrix(std::pair<double**, int> m){
    n_ = m.second;
    A = new double* [n_];
    for(int i = 0; i < n_; i++){
        A[i] = new double [n_ + 1];
    }
    for (int i = 0; i < n_; i++){
        for (int j = 0; j < n_ + 1; j++){
            A[i][j] = m.first[i][j];
        }
    }
    det = det_(A, n_);
}

Matrix& Matrix::operator= (Matrix&& m) {
    if (&m == this) {
        return *this;
    }

    for(int i = 0; i < n_; i++){
        delete[] A[i];
    }

    n_ = m.n_;
    det = m.det;

    for (int i = 0; i < n_; i++) {
        A[i] = m.A[i];
    }

    for(int i = 0; i < n_; i++){
        m.A[i] = nullptr;
    }

    return *this;
}

bool Matrix::main_diagonal() const { //проверка на то, €вл€ютс€ ли элементы главной диагонали нулевыми (можно ли на них делить)
    for (int i = 0; i < n_; i++){
        for (int j = 0; j < n_ + 1; j++){
            if (i == j){
                if (A[i][j] == 0)
                    return false;
            }
        }
    }
    return true;
}

double Matrix::determ() const {
    return det_(A, n_);
}

std::pair<double**, int> Matrix::GetA() const {
    double **A_copy = new double* [n_];

    for (int i = 0; i < n_; i++) {
        A_copy[i] = new double [n_ + 1];
    }

    for (int i = 0; i < n_; i++) {
        for (int j = 0; j < n_ + 1; j++) {
            A_copy[i][j] = A[i][j];
        }
    }

    return std::make_pair(A_copy, n_);
}

Matrix::~Matrix(){
    for (int i = 0; i < n_; i++) {
        delete [] A[i];
    }
}

double* Matrix::operator[](int i){
    return A[i];
}

std::ostream& operator<< (std::ostream &out, const Matrix& matrix){
    bool first = true;
    for (int i = 0; i < matrix.n_; i++){
        if (!first)
            out << std::endl;

        for (int j = 0; j < matrix.n_ + 1; j++){
            std::cout << std::setw(14);
            std::cout << std::fixed << std::setprecision(8);
            out << matrix.A[i][j] << " ";
        }

        first = false;
    }
    return out;
}
