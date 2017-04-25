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
    Level(QWidget *parent = 0, int level = 0);
    ~Level();

    Plate* plate();
    Ball* ball();

    void load_scene();
    void load_bricks();
    bool solved();
    void next_level();
    void repeat_level();
    void clean();

    double scaled(double x);

    static const char* plate_pic_address;
    static const char* ball_pic_address;
    static const char* brick_pic_address;
    static const char* bullet_pic_address;

    static const double default_ball_radius;
    static const double default_ball_speed;
    static const double default_ball_angle;
    static const double default_ball_timer_interval;
    static const double default_bullet_radius;
    static const double default_bullet_speed;
    static const double default_bullet_timer_interval;
    static const double default_plate_excess;
    static const double default_plate_radius;
    static const double default_plate_move;
    static const double default_plate_resize_height;
    static const double default_plate_resize_width;

    static const double min_ball_timer_interval;
    static const double max_plate_excess;
    static const double max_plate_length;
    static const double min_plate_excess;
    static const double min_plate_length;

public slots:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);

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
