#include "rtm.h"

double Pi(double ai, double bi, double ci, double P){
	return (-ci / (bi + ai*P));
}

double Qi(double ai, double bi, double di, double P, double Q){
	return ((di - ai * Q) / (bi + ai * P));
}

std::vector<double> rtm(const Matrix& M){
	int n = M.GetA().second;
	double** x = M.GetA().first;

	double* P = new double [n];
	double* Q = new double [n];

	for (int i = 0; i < n; i++){
		if(i == 0){
			P[i] = Pi(0, x[i][i], x[i][i + 1], 0);
			Q[i] = Qi(0, x[i][i], x[i][n], 0, 0);
		} else if (i == n - 1){
			P[i] = Pi(x[i][i - 1], x[i][i], 0, P[i - 1]);
			Q[i] = Qi(x[i][i - 1], x[i][i], x[i][n], P[i - 1], Q[i - 1]);
		} else {
			P[i] = Pi(x[i][i - 1], x[i][i], x[i][i + 1], P[i - 1]);
			Q[i] = Qi(x[i][i - 1], x[i][i], x[i][n], P[i - 1], Q[i - 1]);
		}
	}

    std::vector<double> answer(n);

	for (int i = n - 1; i >= 0; i--){
		answer[i] = (i == n - 1) ? Q[i] : Q[i] + P[i] * answer[i + 1];
//		std::cout << answer[i] << " ";
	}
    delete[] P;
    delete[] Q;
    return answer;
}
