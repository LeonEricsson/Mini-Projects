/*
 * TDDD86 Tiles
 * This client program uses your TileList class and contains the 'main'
 * function to set up the overall program's graphical user interface.
 * Your code should work properly with an unmodified version of this file.
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow view;
    view.show();
    TileList t;
    return a.exec(); // start Qt event loop
}





distance = math.inf;
for key in board:
    a = key[0] - x
    b = key[1] - y
    c = math.sqrt(abs(a)**2 + abs(b)**2)
    if c < distance:
        distance = c


