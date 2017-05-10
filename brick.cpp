#include "brick.h"
#include "level.h"
#include "package.h"
#include <QDebug>
#include <QGraphicsColorizeEffect>
#include <QGraphicsPixmapItem>

extern Level *level;

Brick::Brick(double w, double h, double x, double y, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _width = w;
    _height = h;
    _frozen = false;
    setPixmap(QPixmap(level->brick_pic_address).scaled(w, h));
    setPos(x, y);
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
    if(_frozen)
        return;

    _frozen = true;
    _ice = new QGraphicsPixmapItem;

    _ice->setPixmap(QPixmap(level->brick_pic_address).scaled(_width+2, _height+3));
    _ice->setPos(x()-1, y());
    QGraphicsColorizeEffect *effect=new QGraphicsColorizeEffect;
    effect->setColor(QColor(20, 130, 150));
    _ice->setGraphicsEffect(effect);
    level->scene()->addItem(_ice);
    _ice->setOpacity(0);
}

void Brick::freeze(double ice_opacity_increase) {
    if(!_frozen || _ice->opacity() + ice_opacity_increase >= 0.9)
        return;
    _ice->setOpacity(_ice->opacity() + ice_opacity_increase);
}

void Brick::hit() {

    if(_frozen) {
        _frozen = false;
        level->scene()->removeItem(_ice);
        delete _ice;
    }

    else {
        scene()->removeItem(this);
        delete this;
        new Package(pos().x(), pos().y());
    }
}
