#ifndef BULLET
#define BULLET

#include <QGraphicsPixmapItem>
#include <QObject>


class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent = 0);
    Bullet(int x, int y, double angle = 0, QGraphicsItem * parent = 0);
    void destroy();

public slots:
    void move();

private:
    double _angle;
    double _speed;
};

#endif // BULLET

