#ifndef BULLET
#define BULLET

#include <QGraphicsPixmapItem>
#include <QObject>


class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(double angle = 0, QGraphicsItem * parent = 0);
public slots:
    void move();
private:
    double _angle;
    double _speed;
};

#endif // BULLET

