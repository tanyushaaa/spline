#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "spline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    double SPolinom(std::vector<double>& S, double x);
    void drawAxes();
    void drawGraph(std::vector<std::vector<double>>& Si);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int width, height;
    double Ox, Oy;
    double step;
    double pixX, pixY;
    double rightX, leftX;
    double rightY, leftY;
};
#endif // MAINWINDOW_H
