#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <string>
#include "plate.h"
#include "ball.h"

class Level : public QGraphicsView
{
public:
    Level(QWidget *parent = 0);
    ~Level();
    Plate* plate();


 public slots:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);

    static const char* plate_pic_address;
    static const char* ball_pic_address;

private:
    QGraphicsScene *_scene;
    Plate *_plate;
    Ball *_ball;
};

#endif // LEVEL_H
