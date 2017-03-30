#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "plate.h"
#include "ball.h"

class Level : public QGraphicsView
{
public:
    Level(QWidget *parent=0);
    ~Level();
    Plate* plate();

private:
    QGraphicsScene *_scene;
    Plate *_plate;
    Ball *_ball;
};

#endif // LEVEL_H
