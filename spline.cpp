#include "spline.h"

std::vector<std::pair<double, double>> XY {{1.415, 0.888551},
											 {1.420, 0.889559},
											 {1.425, 0.890637},
											 {1.430, 0.891667},
											 {1.435, 0.892687},
                                             {1.440, 0.893698}};

/*
std::vector<std::pair<double, double>> XY {{0., 2.},
                                             {1., 4.},
                                             {3., 6.},
                                             {6., 7.},
                                             {10., 3.}};*/

int n = XY.size();

std::vector<double> find_h(){
    double h_prev = 0;
	std::vector<double> h;
    for(const auto& i : XY){
        if (i == *XY.begin()){
			h_prev = i.first;
		} else {
			h.push_back(i.first - h_prev);
			h_prev = i.first;
		}
	}
	return h;
}

std::vector<double> spline(std::vector<double>& hi){
    Matrix mtrx(n - 2);

	for(int i = 0; i < n - 2; i++){
		for(int j = 0; j < n - 1; j++){
            if (j == n - 2){
                mtrx[i][j] = (XY[i + 2].second - XY[i + 1].second) / hi[i + 1] - (XY[i + 1].second - XY[i].second) / hi[i];
            } else if (j == i - 1){
                mtrx[i][j] = hi[i] / 6;
			} else if (i == j){
                mtrx[i][j] = (hi[i] + hi[i + 1]) / 3;
			} else if (j == i + 1){
                mtrx[i][j] = hi[i + 1] / 6;
            } else {
                mtrx[i][j] = 0;
			}
		}
	}

    return rtm(mtrx);
}

std::vector<double> S(int i, std::vector<double>& m, std::vector<double>& hi){ //m2, m3, m4, m5, m6, no indexaciya s nulya
    double mi_ = 0., mi = 0.;
    if (i < 2 || i > n){
        std::cerr << "ban" << std::endl;
    } else {
        if (i != 2){
          mi_ = m[i - 3];
        }
        if (i != n){
            mi = m[i - 2];
        }
    }

    double x3 = (mi - mi_) / (6 * hi[i - 2]);
    double x2 = 3 * (mi_ * XY[i - 1].first - mi * XY[i - 2].first) / (6 * hi[i - 2]);
    double x1 = (3 * (mi * std::pow(XY[i - 2].first, 2) - mi_ * std::pow(XY[i - 1].first, 2))
              + 6 * (XY[i - 1].second - XY[i - 2].second) + std::pow(hi[i - 2], 2) * (mi_ - mi))
              / (6 * hi[i - 2]);
    double x0 = (mi_ * std::pow(XY[i - 1].first, 3) - mi * std::pow(XY[i - 2].first, 3)
              + 6 * (XY[i - 1].first * XY[i - 2].second - XY[i - 2].first * XY[i - 1].second)
              + std::pow(hi[i - 2], 2) * (mi * XY[i - 2].first - mi_ * XY[i - 1].first))
              / (6 * hi[i - 2]);
    if (i == 3){

    }

    return std::vector<double>{x3, x2, x1, x0};
}

QString getStringPolinome(std::vector<double>& polinome){
    std::stringstream out;
    out << std::fixed << std::setprecision(6);
    bool first = true;
    for (unsigned long int i = 0; i < polinome.size(); i++){
        if (polinome[i] != 0){
            if (!first){
                out << std::showpos;
            }
            out << std::setw(15) << polinome[i];
            if(first){
                first = false;
            }
            if (i != polinome.size() - 1){
                out << " * x";
                if (i != polinome.size() - 2){
                    out << "^" << polinome.size() - i - 1;
                }
            }
        }
    }
    return QString::fromLatin1(out.str().data(), out.str().size());
}
