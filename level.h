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
    Level(int level = 0, QWidget *parent = 0);
    ~Level();
    Plate* plate();

    void load_scene();
    void load_bricks();
    bool solved();
    void next_level();
    void repeat_level();
    void clean();

    static const char* plate_pic_address;
    static const char* ball_pic_address;
    static const char* brick_pic_address;
    static const char* bullet_pic_address;

public slots:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    QGraphicsScene *_scene;
    Plate *_plate;
    Ball *_ball;
    int _level;
    bool _finished;

    int bricks_row;
    int bricks_column;
    int bricks_space;
};

#endif // LEVEL_H
