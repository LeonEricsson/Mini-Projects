/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include <unordered_map>
#include <set>

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

struct lessSlope  {
        lessSlope(Point* p){
            this->p = p;
        }
        Point* p;
        bool operator()(Point p1, Point p2) {
            return p->slopeTo(p1) < p->slopeTo(p2);
        }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input800.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();
    auto begin = chrono::high_resolution_clock::now();


    map<double, vector<Point>> sortedPoints;
    map<Point, Point> drawnLines;
    for(Point p: points){
        for(Point p1 : points){
            if(sortedPoints.count(p.slopeTo(p1)) == 0){
                vector<Point> temp;
                temp.push_back(p1);
                sortedPoints.insert(pair<double, vector<Point>>(p.slopeTo(p1), temp));
            }
            else {
               sortedPoints.find(p.slopeTo(p1))->second.push_back(p1);
            }
        }
        for(auto it = sortedPoints.begin(); it != sortedPoints.end() ; it++){
            if(it->second.size() > 2){
                it->second.push_back(p);
                sort(it->second.begin(), it->second.end());
                if(drawnLines.find(it->second.front()) != drawnLines.end()){
                    Point p = drawnLines.at(it->second.front());
                    Point p1 = it->second.back();
                    if(p.x != p1.x ||  p.y != p1.y){
                        render_line(scene, it->second.front(), it->second.back());
                        drawnLines.insert(pair<Point, Point>(it->second.front(), it->second.back()));
                        a.processEvents();
                    }
                }
                else {
                    render_line(scene, it->second.front(), it->second.back());
                    drawnLines.insert(pair<Point, Point>(it->second.front(), it->second.back()));
                    a.processEvents();
                }
            }
        }
        sortedPoints.clear();
    }




    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}

