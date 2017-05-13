#ifndef BRICK_H
#define BRICK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "package.h"

class Brick : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Brick(QString pic_addr, double w, double h, double x = 5, double y = 5, QGraphicsItem *parent = 0);
    double width();
    double height();
    bool frozen();

    QPointF top_left();
    QPointF top_right();
    QPointF bottom_left();
    QPointF bottom_right();

    void hit();
    void create_ice();
    void freeze(double ice_opacity_increase = 0.02);
    void unfreeze();

    void randomize_package(double x, double y);

protected:
    double _width;
    double _height;
    QGraphicsPixmapItem * _ice;
};

class YellowBrick : public Brick
{
public:
    YellowBrick(double w, double h, double x = 5, double y = 5, QGraphicsItem *parent = 0);
};

class RedBrick : public Brick
{
public:
    RedBrick(double w, double h, double x = 5, double y = 5, QGraphicsItem *parent = 0);
};

class GreenBrick : public Brick
{
public:
    GreenBrick(double w, double h, double x = 5, double y = 5, QGraphicsItem *parent = 0);
};

class BlueBrick : public Brick
{
public:
    BlueBrick(double w, double h, double x = 5, double y = 5, QGraphicsItem *parent = 0);
};

class OldBrick : public Brick
{
public:
    OldBrick(double w, double h, double x = 5, double y = 5, QGraphicsItem *parent = 0);
};

class FrozenBrick : public Brick
{
public:
    FrozenBrick(double w, double h, double x = 5, double y = 5, QGraphicsItem *parent = 0);
};


#endif // BRICK_H
