#include "brick.h"
#include "level.h"
#include <qdebug.h>

extern Level *level;

Brick::Brick(double w, double h, double x, double y, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _width = w;
    _height = h;
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
