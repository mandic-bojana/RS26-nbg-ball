#include "plate.h"
#include <QDebug>
#include <math.h>

Plate::Plate(QGraphicsView* view, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _excess = 40;
    _r = 150;
    setPixmap(QPixmap(":/images/plate.png").scaled(300, 300));
    setPos(view->width()/2 - r(), view->height() - _excess);
}

void Plate::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Right)
        setX(pos().x() + 10);
    else if(event->key()==Qt::Key_Left)
        setX(pos().x() - 10);
}

void Plate::resize_width(double dx) {
    QPointF A(pos().x() + r() + sqrt(r()*r() - (r()-_excess)*(r()-_excess)), pos().y() + _excess);
    QPointF AP = A + QPointF(dx, 0);
    QPointF T(pos().x() + r(), pos().y());
    QPointF S = (AP + T)/2;
    QPointF v = T - AP;
    QPointF vn(-v.y(), v.x());
    double t = (T.x() - S.x()) / vn.x();
    double y = S.y() + t * vn.y();
    double R = y - T.y();
    double len = 2*(AP.x()-T.x());
    if(len <= max_length && len >= min_length) {
        setX(x() - R);
        _r = R;
        setPixmap(QPixmap(":/images/plate.png").scaled(2*R, 2*R));
    }
}

void Plate::resize_height(double dx) {
    if(_excess + dx <= max_excess && _excess + dx >= min_excess) {
        QPointF A(pos().x() + r() + sqrt(r()*r() - (r()-_excess)*(r()-_excess)), pos().y() + _excess);
        QPointF T(pos().x() + r(), pos().y());
        QPointF TP = T - QPointF(0, dx);
        QPointF S = (A + TP) / 2;
        QPointF v = TP - A;
        QPointF vn(-v.y(), v.x());
        double t = (T.x() - S.x()) / vn.x();
        double y = S.y() + t * vn.y();
        double R = y - TP.y();

        _excess += dx;
        setY(TP.y());
        setX(x() - R);
        _r = R;
        setPixmap(QPixmap(":/images/plate.png").scaled(2*R, 2*R));
    }
}

double Plate::x() {
    return pos().x() + r();
}

double Plate::y() {
    return pos().y() + r();
}

double Plate::r() {
    return _r;
}

double Plate::excess()
{
    return _excess;
}
