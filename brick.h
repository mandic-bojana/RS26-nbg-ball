#ifndef BRICK_H
#define BRICK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>

class Brick : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Brick(double w = 40, double h = 20, double x = 5, double y = 5, QGraphicsItem *parent = 0);
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

private:
    double _width;
    double _height;
    bool _frozen;
    QGraphicsPixmapItem * _ice;
};

#endif // BRICK_H
