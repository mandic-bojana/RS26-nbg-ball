#include "bullet.h"
#include "level.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <math.h>
#include <QSound>

extern Level *level;

Bullet::Bullet(QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _r = level->scaled(level->default_bullet_radius);
    setPixmap(QPixmap(level->bullet_pic_address).scaled(2*_r, 2*_r));
    setRotation(_angle = 0);
    _speed = level->scaled(level->default_bullet_speed);
    setPos(level->plate()->top() - QPointF(_r, _r));


    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(level->default_bullet_timer_interval);
    QSound::play(level->gunshot_sound);
}

Bullet::Bullet(int x, int y, double angle, QGraphicsItem *parent)
    : Bullet(parent) {
    setPos(x, y);
    setRotation(_angle = angle);
}

void Bullet::move() {
    // kada je ugao 0, metak se krece na gore
    setPos(x() + _speed * sin(_angle), y() - _speed * cos(_angle));

    if(pos().y() + pixmap().width() < 0) {
        destroy();
        return;
    }

    QList<Brick*> bricks = level->bricks();
    QList<Brick*>::iterator it = bricks.begin();
    QList<Brick*>::iterator it_end = bricks.end();
    bool hit = false;
    for(;it != it_end; it++) {
        if(collidesWithItem(*it)) {
            Brick* brick = (Brick*)*it;
            brick->hit();
            QSound::play(level->hit_sound);
            hit = true;
        }
    }

    if(hit)
        destroy();

    if(level->solved())
        level->clean();
}

void Bullet::destroy() {
    scene()->removeItem(this);
    delete this;
}
