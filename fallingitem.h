#ifndef FALLINGITEM_H
#define FALLINGITEM_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <math.h>


class FallingItem: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    FallingItem(const QString picture_address, double length, QGraphicsItem * parent = 0);
    FallingItem(const QString picture_address, int x, int y, double length, double angle = M_PI/2, QGraphicsItem * parent = 0);
    void destroy();

public slots:
    virtual void move();

private:
    int _side;
    double _angle;
    double _speed;
    double _length;
};

#endif // FALLINGITEM_H
