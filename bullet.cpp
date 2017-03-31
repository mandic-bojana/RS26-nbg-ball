#include "bullet.h"
#include "level.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <math.h>

extern Level *level;

Bullet::Bullet(double angle, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), _angle(angle), _speed(10) {
    setPixmap(QPixmap(level->bullet_pic_address));
    setRotation(angle);

    QTimer* timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);
}

void Bullet::move() {
    // kada je ugao 0, metak se krece na gore
    setPos(x() + _speed * sin(_angle), y() - _speed * cos(_angle));

    if(pos().y() + pixmap().width() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
