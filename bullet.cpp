#include "bullet.h"
#include "level.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <math.h>
#include <typeinfo>

extern Level *level;

Bullet::Bullet(double angle, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), _angle(angle), _speed(10) {
    setPixmap(QPixmap(level->bullet_pic_address));
    setRotation(angle);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);
}

void Bullet::move() {
    // kada je ugao 0, metak se krece na gore
    setPos(x() + _speed * sin(_angle), y() - _speed * cos(_angle));

    if(pos().y() + pixmap().width() < 0)
        destroy();

    QList<QGraphicsItem*> colliding_items = collidingItems();
    QList<QGraphicsItem*>::iterator it = colliding_items.begin();
    QList<QGraphicsItem*>::iterator it_end = colliding_items.end();

    bool hit = false;
    for(;it != it_end; it++) {
        if(typeid(**it) == typeid(Brick)) {
            Brick* brick = (Brick*)*it;
            brick->hit();
            hit = true;
        }
    }

    if(level->solved())
        level->clean();

    /*if(hit)
        destroy();*/
}

void Bullet::destroy() {
    scene()->removeItem(this);
    delete this;
}
