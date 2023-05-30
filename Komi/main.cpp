#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QVector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include "graphwidget.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QVector<Point> points;
    points.append({100, 0});
    points.append({0, 70});
    points.append({50, 100});
    points.append({150, 80});
    points.append({100, 300});
    points.append({-20, 200});

    QVector<Edge> edges;
    edges.append({0, 1, 17});
    edges.append({0, 2, 21});
    edges.append({0, 3, 48});
    edges.append({1, 2, 25});
    edges.append({2, 3, 6});
    edges.append({3, 4, 13});
    edges.append({4, 2, 8});
    edges.append({4, 5, 40});
    edges.append({5, 1, 3});

    GraphWidget graphWidget(points, edges);
    graphWidget.show();

    return app.exec();
}
