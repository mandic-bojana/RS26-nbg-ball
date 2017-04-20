#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <string>
#include <vector>
#include "plate.h"
#include "brick.h"
#include "ball.h"

using namespace std;

class Level : public QGraphicsView
{
public:
    Level(QWidget *parent = 0);
    ~Level();
    Plate* plate();

 public slots:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    static const char* plate_pic_address;
    static const char* ball_pic_address;
    static const char* brick_pic_address;
    static const char* bullet_pic_address;

private:
    QGraphicsScene *_scene;
    Plate *_plate;
    Ball *_ball;

    int bricks_row;
    int bricks_column;
    int bricks_space;
};

#endif // LEVEL_H
