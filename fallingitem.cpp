#include "fallingitem.h"
#include "level.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <cmath>
#include <typeinfo>


extern Level *level;
FallingItem::FallingItem(const QString picture_address, double length, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), _length(length) {

    setPixmap(QPixmap(picture_address).scaled(_length, _length));

    _speed = level->scaled(level->default_fallingitem_speed);
    setPos(qrand() % int(level->scene()->width()), 0);

    level->scene()->addItem(this);

    _side = qrand()%3-1;
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(level->default_fallingitem_timer_interval);
}

FallingItem::FallingItem(const QString picture_address, int x, int y, double length, double angle, QGraphicsItem *parent)
    : FallingItem(picture_address, length, parent) {
    setPos(x, y);
    setRotation(_angle = angle);
}

void FallingItem::move() {
    _angle += _side*0.03;
    if(abs(_angle - M_PI/2) >= M_PI/6)
        _side *= -1;
    setPos(x() + _speed * cos(_angle), y() + _speed * sin(_angle));

    if(pos().y() > level->scene()->height())
        destroy();
}

void FallingItem::destroy() {
    scene()->removeItem(this);
    delete this;
}

