#include "brick.h"
#include "level.h"
#include "package.h"
#include <QDebug>
#include <QGraphicsColorizeEffect>
#include <QGraphicsPixmapItem>

extern Level *level;

Brick::Brick(QString pic_addr, double w, double h, double x, double y, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _width = w;
    _height = h;
    setPixmap(QPixmap(pic_addr).scaled(w, h));
    setPos(x, y);

    _ice = nullptr;
}

double Brick::width() {
    return _width;
}

double Brick::height() {
    return _height;
}

QPointF Brick::top_left() {
    return pos();
}

QPointF Brick::top_right() {
    return pos() + QPointF(_width, 0);
}

QPointF Brick::bottom_left() {
    return pos() + QPointF(0, _height);
}

QPointF Brick::bottom_right() {
    return pos() + QPointF(_width, _height);

}

void Brick::create_ice() {
    if(_ice)
        return;

    _ice = new QGraphicsPixmapItem;

    _ice->setPixmap(QPixmap(level->yellow_brick_pic_address).scaled(_width+2, _height+3));
    _ice->setPos(x()-1, y());
    QGraphicsColorizeEffect *effect=new QGraphicsColorizeEffect;
    effect->setColor(QColor(20, 130, 150));
    _ice->setGraphicsEffect(effect);
    level->scene()->addItem(_ice);
    _ice->setOpacity(0);
}

void Brick::freeze(double ice_opacity_increase) {
    if(!_ice || _ice->opacity() + ice_opacity_increase >= 0.9)
        return;
    _ice->setOpacity(_ice->opacity() + ice_opacity_increase);
}

void Brick::unfreeze() {
    if(_ice) {
        level->scene()->removeItem(_ice);
        delete _ice;
        _ice = nullptr;
    }
}

void Brick::hit() {
    if(_ice)
        unfreeze();
    else {
        randomize_package(pos().x(), pos().y());
        scene()->removeItem(this);
        delete this;
    }
}

void Brick::randomize_package(double x, double y) {
    int rand = (level->mode_name() == Samurai) ? qrand() % 600 : qrand() % 200;
    if(rand < 2)
        new IncreasePlateLength(x, y);
    else if(rand < 4)
        new DecreasePlateLength(x, y);
    else if(rand < 6)
        new IncreasePlateWidth(x, y);
    else if(rand < 8)
        new DecreasePlateWidth(x, y);
    else if(rand < 10)
        new SamuraiModeActivate(x, y);
    else if(rand < 12)
        new WinterModeActivate(x, y);
    else if(rand < 14)
        new FireModeActivate(x, y);
    else if(rand < 16)
        new SpeedModeActivate(x, y);
    else if(rand < 18)
        new DefaultModeActivate(x, y);
}

YellowBrick::YellowBrick(double w, double h, double x, double y, QGraphicsItem *parent)
    : Brick(level->yellow_brick_pic_address, w, h, x, y, parent) { }

RedBrick::RedBrick(double w, double h, double x, double y, QGraphicsItem *parent)
    : Brick(level->red_brick_pic_address, w, h, x, y, parent) { }

GreenBrick::GreenBrick(double w, double h, double x, double y, QGraphicsItem *parent)
    : Brick(level->green_brick_pic_address, w, h, x, y, parent) { }

BlueBrick::BlueBrick(double w, double h, double x, double y, QGraphicsItem *parent)
    : Brick(level->blue_brick_pic_address, w, h, x, y, parent) { }

OldBrick::OldBrick(double w, double h, double x, double y, QGraphicsItem *parent)
    : Brick(level->old_brick_pic_address, w, h, x, y, parent) { }
