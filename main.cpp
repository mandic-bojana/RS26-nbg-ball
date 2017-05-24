#include "level.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QDesktopWidget>

Level *level;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;

    QRect desktop = app.desktop()->geometry();
    int w = desktop.width();
    int h = desktop.height();
    int x =  0, y = 0;

    if(3*w < 4*h) {
        y = (h - (double)w*3/4)/2;
        h = (double)w*3/4;
    }
    else {
        x = (w - (double)h*4/3)/2;
        w = (double)h*4/3;
    }

    level = new Level(&window, 5);
    level->setGeometry(x, y, w, h);
    level->load_scene();

    window.showFullScreen();

    return app.exec();
}
