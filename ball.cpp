#include "ball.h"
#include "level.h"
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
    speed = 5;
    active = false;

    setPixmap(QPixmap(level->ball_pic_address).scaled(2*_r, 2*_r));
    setPos(-_r + view->width()/2, view->height() - /*excess*/30 - 2*_r);

    interval = 13;
    _timer = new QTimer();
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(move()));
}

Ball::~Ball() {
    _timer->stop();
    delete _timer;
}

double d2(QPointF A, QPointF B) {
    return (A.x() - B.x()) * (A.x() - B.x()) + (A.y() - B.y()) * (A.y() - B.y());
}

double d(QPointF A, QPointF B) {
    return sqrt(d2(A, B));
}

double Ball::angle_to(QPointF P) {
    QPointF v = P - C();
    double fi = atan2(v.y(), v.x());
    return -fi;
}

bool Ball::is_active() {
    return active;
}

void Ball::activate() {
    active = true;
    _timer->start(interval);
}

void Ball::move() {
    setPos(pos().x() + speed * cos(angle), pos().y() - speed * sin(angle));

    if(pos().y() + r() >= scene()->height()) {
        level->clean();
        level->repeat_level();
        return;
    }
    else if(pos().y() <= 0 && goes_up())
        bounce_horizontal();
    if(pos().x() + 2*_r >= scene()->width() && goes_right())
        bounce_vertical();
    else if(pos().x() <= 0 && goes_left())
        bounce_vertical();
    if(d(level->plate()->center(), C()) <= level->plate()->r() + r() && goes_to(level->plate()->center()))
        bounce_point(level->plate()->center());

    QList<QGraphicsItem*> colliding_items = collidingItems();
    QList<QGraphicsItem*>::iterator it = colliding_items.begin();
    QList<QGraphicsItem*>::iterator it_end = colliding_items.end();
    for(;it != it_end; it++) {
        if(typeid(**it) == typeid(Brick)) {
            Brick* brick = (Brick*)*it;
            if(bounce_brick(brick))
                brick->hit();
        }
    }

    if(level->solved())
        level->clean();

    if(_timer->interval() > 8) {
        interval -= 0.0001;
        _timer->setInterval(interval);
    }
}

bool Ball::bounce_brick(Brick* brick) {
    if(x() >= brick->x() && x() <= brick->x() + brick->width() && y() < brick->y() && goes_down()) //odozgo
        bounce_horizontal();
    else if(x() >= brick->x() && x() <= brick->x() + brick->width() && y() > brick->y() + brick->height() && goes_up()) //odozdo
        bounce_horizontal();
    else if(y() >= brick->y() && y() <= brick->y() + brick->height() && x() < brick->x() && goes_right()) //sleva
        bounce_vertical();
    else if(y() >= brick->y() && y() <= brick->y() + brick->height() && x() > brick->x() + brick->width() && goes_left()) //zdesna
        bounce_vertical();
    else if(x() >= brick->x() + brick->width() && y() <= brick->y() && goes_to(brick->top_right())) //gore-desno
        bounce_point(brick->top_right());
    else if(x() >= brick->x() + brick->width() && y() >= brick->y() + brick->height() && goes_to(brick->bottom_right())) //dole-desno
        bounce_point(brick->bottom_right());
    else if(x() <= brick->x() && y() <= brick->y() && goes_to(brick->top_left())) //gore-levo
        bounce_point(brick->top_left());
    else if(x() <= brick->x() && y() >= brick->y() + brick->height() && goes_to(brick->bottom_left())) //dole-levo
        bounce_point(brick->bottom_left());
    else return false;
    return true;
}

void Ball::bounce_point(double px, double py) {
    bounce_point(QPointF(px, py));
}

void Ball::bounce_point(QPointF P) {
    bounce(M_PI/2 + angle_to(P));
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

bool Ball::goes_to(double px, double py) {
    return goes_to(QPointF(px, py));
}

bool Ball::goes_to(QPointF P) {
    return cos(angle_to(P) - angle) > 0;
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
