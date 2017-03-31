#include "plate.h"
#include "level.h"
#include <QDebug>
#include <math.h>

extern Level *level;

Plate::Plate(QGraphicsView *view, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _excess = 40;
    _r = 150;
    setPixmap(QPixmap(level->plate_pic_address).scaled(300, 300));
    setPos(view->width()/2 - r(), view->height() - _excess);
}

void Plate::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Right)
        move(10);
    else if(event->key()==Qt::Key_Left)
        move(-10);
}


void Plate::resize_width(double d) {
    QPointF A = right();
    QPointF AP = A + QPointF(d, 0);
    QPointF T = top();
    QPointF S = (AP + T)/2;
    QPointF v = T - AP;                             //vektor
    QPointF vn(-v.y(), v.x());                      //vektor normale
    double t = (T.x() - S.x()) / vn.x();            //koeficijent
    double y = S.y() + t * vn.y();                  //y koordinata novog centra
    double R = y - T.y();                           //novi poluprecnik
    double len = 2*(AP.x()-T.x());                  //nova duzina podloge

    if(len <= max_length && len >= min_length) {
        setX(x() - R);
        _r = R;
        setPixmap(QPixmap(level->plate_pic_address).scaled(2*R, 2*R));
    }
}

void Plate::resize_height(double d) {
    if(_excess + d <= max_excess && _excess + d >= min_excess) {
        QPointF A = right();
        QPointF T = top();
        QPointF TP = T - QPointF(0, d);
        QPointF S = (A + TP) / 2;
        QPointF v = TP - A;                         //vektor
        QPointF vn(-v.y(), v.x());                  //vektor normale
        double t = (T.x() - S.x()) / vn.x();        //koeficijent
        double y = S.y() + t * vn.y();              //y koordinata novog centra
        double R = y - TP.y();                      //novi poluprecnik

        _excess += d;
        setY(TP.y());
        setX(x() - R);
        _r = R;
        setPixmap(QPixmap(level->plate_pic_address).scaled(2*R, 2*R));
    }
}

void Plate::move(double d) {
    if(left().x() + d >= 0 && right().x() + d <= scene()->width())
        setX(pos().x() + d);
}

QPointF Plate::left() {
    return QPointF(pos().x() + r() - sqrt(r()*r() - (r()-_excess)*(r()-_excess)), pos().y() + _excess);
}

QPointF Plate::right() {
    return QPointF(pos().x() + r() + sqrt(r()*r() - (r()-_excess)*(r()-_excess)), pos().y() + _excess);
}

QPointF Plate::top() {
    return QPointF(pos().x() + r(), pos().y());
}

QPointF Plate::center() {
    return QPointF(pos().x() + r(), pos().y() + r());
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

const double Plate::max_excess = 100;
const double Plate::max_length = 400;
const double Plate::min_excess = 20;
const double Plate::min_length = 50;
