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

private:
    double _width;
    double _height;
};

#endif // BRICK_H
