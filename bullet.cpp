#include "bullet.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <math.h>

Bullet::Bullet(double angle, QGraphicsItem* parent):
    _angle(angle), QGraphicsPixmapItem(parent), QObject() {

    setPixmap(QPixmap(":/images/bullet.png"));
    setRotation(angle);

    QTimer* timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);
}

void Bullet::move()
{
    // kada je ugao 0, metak se krece na gore
    setPos(x() + 10 * sin(_angle), y() - 10 * cos(_angle));

    if(pos().y() + 10 < 0){
        scene()->removeItem(this);
        qDebug()<<"bullet deleted";
        delete this;
    }
}
