#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    leftX = XY[0].first - 0.003;
    rightX = XY[n - 1].first + 0.003;
    leftY = XY[0].second - 0.003;
    rightY = XY[n - 1].second + 0.003;

    width = (rightX - leftX) * 30000;
    height = (rightX - leftX) * 30000;

    step = 0.0001;
    pixX = width / (rightX - leftX);
    pixY = height / (rightY - leftY);
    Ox = - leftX;
    Oy = rightY;
}

double MainWindow::SPolinom(std::vector<double>& S, double x){
    return (S[0] * std::pow(x, 3) + S[1] * std::pow(x, 2) + S[2] * x + S[3]) * (-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawGraph(std::vector<std::vector<double>>& Si){
    QPixmap graph(width, height);
    QPainter paint;

    paint.begin(&graph);
    paint.eraseRect(0, 0, width, height);


    QString axes = "%1";
    int cnt = 0;
    for(double k = 0; k < width; k += 0.0005){
        if ((cnt % 4) == 0){
            paint.setPen(Qt::darkGray);
            paint.drawText((k - 0.0005) * pixX, 0.0091 * pixY, axes.arg(k - Ox));
        }
        paint.setPen(QPen(Qt::lightGray, 0.3, Qt::DashLine));
        paint.drawLine(k * pixX, 0, k  * pixX, height);
        cnt++;
    }
    cnt = 0;
    for(double k = 0; k < height; k += 0.00025){
        if ((cnt % 2) == 0){
            paint.setPen(Qt::darkGray);
            paint.drawText(0.001 * Ox, k * pixY, axes.arg(Oy - k));
        }
        paint.setPen(QPen(Qt::lightGray, 0.3, Qt::DashLine));
       // paint.setPen(QPen(Qt::lightGray, 1));
        paint.drawLine(0, k * pixY, width, k * pixY);
        cnt++;
    }

    QString coord = "%1; %2";

    for(const auto& i : XY){
        paint.setPen(QPen(Qt::red, 4));
        paint.drawPoint((Ox + i.first) * pixX, (Oy + (-1) * i.second) * pixY);
        paint.setPen(Qt::black);
        paint.drawText((Ox + i.first - 0.002) * pixX, (Oy + (-1) * (i.second + 0.0002)) * pixY, coord.arg(i.first).arg(i.second));
    }

    std::vector<QPainterPath> path(n - 1);
    bool first = true;

    for(int j = 0; j < n - 1; j++){
        for(double i = XY[j].first; i < XY[j + 1].first; i += step){
            if(!std::isnan(SPolinom(Si[j], i))){
                if(first){
                    path[j].moveTo((i + Ox) * pixX, (SPolinom(Si[j], i) + Oy) * pixY);
                    first = false;
                } else {
                    path[j].lineTo((i + Ox) * pixX, (SPolinom(Si[j], i) + Oy) * pixY);
                }
            }
        }
        first = true;
    }

    std::vector<QColor> colors {Qt::darkGreen,
                                Qt::darkBlue,
                                Qt::darkCyan,
                                Qt::darkMagenta,
                                Qt::darkYellow};
    double ustala = 0.0085;
    QString result;
    for(int i = 0; i < n - 1; i++){
        paint.setPen(QPen(colors[i], 1, Qt::SolidLine));
        paint.setRenderHint(QPainter::Antialiasing, true);
        paint.drawPath(path[i]);

        QString S = "S%1 = ";
        QString x = "   \t%1 <= x <= %2";
        result += S.arg(i + 1) + getStringPolinome(Si[i]) + x.arg(XY[i].first).arg(XY[i + 1].first) + '\n';
        paint.drawText(0.0128 * pixX, ustala * pixY,
                       S.arg(i + 1) + getStringPolinome(Si[i]) + x.arg(XY[i].first).arg(XY[i + 1].first));
        ustala -= 0.0005;
    }

    QFile file("result_splines.txt");

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(result.toUtf8());
        file.close();
    }

    //ui->Polinomes->setText(result);
    paint.end();
    ui->Graph->setPixmap(graph);
}
