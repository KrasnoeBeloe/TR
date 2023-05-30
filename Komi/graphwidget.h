#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

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

struct Point {
    double x;
    double y;
};

struct Edge {
    int source;
    int destination;
    double weight;
};

class GraphWidget : public QGraphicsView {
public:
    GraphWidget(QVector<Point>& points, QVector<Edge>& edges, QWidget* parent = nullptr);

    void drawPoints();
    void drawLines();
    void solveTSP();
    void drawOptimalPath();
    void addPoint();
    void removePoint();
    void addEdge();
    void removeEdge();

private:
    QGraphicsScene* scene;
    QVector<Point>& points;
    QVector<Edge>& edges;
    std::vector<int> optimalPath;
    QTextEdit* textOutput;
    double minDistance;
    void updateMinDistance() {
        minDistance = std::numeric_limits<double>::infinity();
        solveTSP();
        textOutput->clear();
        textOutput->append("Minimum distance: " + QString::number(minDistance));
    }
    double calculateDistance(const Point& p1, const Point& p2) {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

#endif // GRAPHWIDGET_H
