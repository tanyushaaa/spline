#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector<double> hi = find_h();
    std::vector<double> mi = spline(hi);

    MainWindow w;
    std::vector<std::vector<double>> Si;
    for (int i = 2; i <= n; i++){
        Si.push_back(S(i, mi, hi));
    }
    w.drawGraph(Si);
    w.show();
    return a.exec();
}
