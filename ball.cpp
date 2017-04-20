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

    interval = 9;
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
    else if(pos().y() <= 0 && goes_up())
        bounce_horizontal();
    if(pos().x() + 2*_r >= scene()->width() && goes_right())
        bounce_vertical();
    else if(pos().x() <= 0 && goes_left())
        bounce_vertical();

    if(collidesWithItem(level->plate()) && goes_to(level->plate()->center())) {
        double k = (x() - level->plate()->x()) / (y() - level->plate()->y());
        double fi = atan(k);
        bounce(fi);
    }

    vector<Brick*> *bricks = level->bricks();
    vector<Brick*>::iterator it = bricks->begin();
    vector<Brick*>::iterator it_end = bricks->end();
    for(;it != it_end; it++) {
        Brick* brick = *it;
        if(collidesWithItem(brick)) {
            if(x() >= brick->x() && x() <= brick->x() + brick->width() && y() < brick->y() && goes_down()) //odozgo
                bounce_horizontal();
            else if(x() >= brick->x() && x() <= brick->x() + brick->width() && y() > brick->y() + brick->height() && goes_up()) //odozdo
                bounce_horizontal();
            else if(y() >= brick->y() && y() <= brick->y() + brick->height() && x() < brick->x() && goes_right()) //sleva
                bounce_vertical();
            else if(y() >= brick->y() && y() <= brick->y() + brick->height() && x() > brick->x() + brick->width() && goes_right()) //zdesna
                bounce_vertical();
            else if(x() >= brick->x() + brick->width() && y() <= brick->y() && goes_to(brick->top_right())) //gore-desno
                bounce_point(brick->top_right());
            else if(x() >= brick->x() + brick->width() && y() >= brick->y() + brick->height() && goes_to(brick->bottom_right())) //dole-desno
                bounce_point(brick->bottom_right());
            else if(x() <= brick->x() && y() <= brick->y() && goes_to(brick->top_left())) //gore-levo
                bounce_point(brick->top_left());
            else if(x() <= brick->x() && y() >= brick->y() + brick->height() && goes_to(brick->bottom_left())) //dole-levo
                bounce_point(brick->bottom_left());
            scene()->removeItem(brick);
            bricks->erase(it);
        }
    }

    if(_timer->interval() >= 6) {
        interval -= 0.001;
        _timer->setInterval(interval);
    }
}

void Ball::bounce_point(double px, double py) {
    double k = (x() - px) / (y() - py);
    double fi = atan(k);
    bounce(fi);
}

void Ball::bounce_point(QPointF P) {
    bounce_point(P.x(), P.y());
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

double d2(QPointF A, QPointF B) {
    return (A.x() - B.x()) * (A.x() - B.x()) + (A.y() - B.y()) * (A.y() - B.y());
}

double d(QPointF A, QPointF B) {
    return sqrt(d2(A, B));
}

bool Ball::goes_to(double px, double py) {
    return goes_to(QPointF(px, py));
}

bool Ball::goes_to(QPointF P) {
    return d2(C() + QPointF(speed * cos(angle), - speed * sin(angle)), P) < d2(C(), P);
}

bool Ball::goes_up() {
    return sin(angle) > 0;
}

bool Ball::goes_down() {
    return !goes_up();
}

bool Ball::goes_left() {
    return cos(angle) < 0;
}

bool Ball::goes_right() {
    return !goes_left();
}

QPointF Ball::C() {
    return QPointF(x(), y());
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
