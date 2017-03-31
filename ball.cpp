#include "ball.h"
#include "level.h"
#include "brick.h"
#include <math.h>
#include <vector>
#include <QDebug>
#include <typeinfo>

using namespace std;

extern Level *level;

Ball::Ball(QGraphicsView *view, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _r = 10;
    angle = 1.5;
    speed = 3;

    setPixmap(QPixmap(level->ball_pic_address).scaled(2*_r, 2*_r));
    setPos(-_r + view->width()/2, view->height() - /*excess*/40 - 2*_r);

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
        _timer->stop();
    }
    if(pos().x() + 2*_r >= scene()->width() || pos().x() <= 0)
        bounce_vertical();
    if(pos().y() <= 0)
        bounce_horizontal();

    if(collidesWithItem(level->plate())) {
        double k = (x() - level->plate()->x()) / (y() - level->plate()->y());
        double fi = atan(k);
        if(angle - fi < 0 || (angle - fi > M_PI && angle - fi < 2*M_PI))
            bounce(fi);
    }

    vector<Brick*> *bricks = level->bricks();
    vector<Brick*>::iterator it = bricks->begin();
    vector<Brick*>::iterator it_end = bricks->end();
    for(;it != it_end; it++) {
        Brick* brick = *it;
        if(collidesWithItem(brick)) {
            if(x() >= brick->x() && x() <= brick->x() + brick->width())
                bounce_horizontal();
            else if(x() >= brick->x() && x() <= brick->x() + brick->width())
                bounce_vertical();
            else if(x() >= brick->x() + brick->width() && y() <= brick->y())
                bounce_point(brick->x() + brick->width(), brick->y());
            else if(x() >= brick->x() + brick->width() && y() >= brick->y() + brick->height())
                bounce_point(brick->x() + brick->width(), brick->y() + brick->height());
            else if(x() <= brick->x() && y() <= brick->y())
                bounce_point(brick->x(), brick->y());
            else if(x() <= brick->x() && y() >= brick->y() + brick->height())
                bounce_point(brick->x(), brick->y() + brick->height());
            scene()->removeItem(brick);
            bricks->erase(it);
        }
    }

    if(_timer->interval()>=3) {
        interval -= 0.001;
        _timer->setInterval(interval);
    }
}

void Ball::bounce_point(double px, double py) {
    double k = (x() - px) / (y() - py);
    double fi = atan(k);
    bounce(fi);
}

void Ball::bounce_point(QPointF p) {
    bounce_point(p.x(), p.y());
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
