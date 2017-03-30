#include "ball.h"
#include "level.h"
#include <math.h>
#include <QDebug>

extern Level *level;

Ball::Ball(QGraphicsView *view, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(level->ball_pic_address).scaled(30, 30));
    setPos(-15 + view->width()/2, view->height() - /*excess*/40 - 30);
    _r = 15;
    angle = 1.5;
    speed = 3;

    interval = 10;
    _timer = new QTimer();
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(move()));
    _timer->start(interval);

}

Ball::~Ball() {
    _timer->stop();
    delete _timer;
}

void Ball::move() {
    setPos(pos().x() + speed * cos(angle), pos().y() - speed * sin(angle));

    if(pos().y() + 2*_r >= scene()->height()+2*_r) {
        qDebug() << "mrtav!" << endl;
        _timer->stop();
    }
    if(pos().x() + 2*_r >= scene()->width() || pos().x() <= 0)
        bounce_vertical();
    if(pos().y() <= 0)
        bounce_horizontal();

    if(collidesWithItem(level->plate())) {
        double k = (x() - level->plate()->x()) / (y() - level->plate()->y());
        double fi = atan(k);
        qDebug() << fi;
        if(angle - fi < 0 || (angle - fi > M_PI && angle - fi < 2*M_PI))
            bounce(fi);
    }

    if(_timer->interval()>=3) {
        interval -= 0.001;
        _timer->setInterval(interval);
    }
}

void Ball::bounce(double alpha) {
    angle = 2 * alpha - angle;
    if(angle < 0)
        angle += 2 * M_PI;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI;
}

void Ball::bounce_vertical() {
    Ball::bounce(M_PI / 2);
}

void Ball::bounce_horizontal() {
    Ball::bounce(0);
}


double Ball::x() {
    return pos().x() + r();
}

double Ball::y() {
    return pos().y() + r();
}

double Ball::r() {
    return _r;
}
