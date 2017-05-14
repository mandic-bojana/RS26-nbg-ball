#include "plate.h"
#include "level.h"
#include <QDebug>
#include <math.h>
#include <bullet.h>

extern Level *level;

Plate::Plate(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    _excess = level->scaled(level->default_plate_excess);
    _r = level->scaled(level->default_plate_radius);

    _pic = QPixmap(level->plate_pic_address);
    _fire_pic = QPixmap(level->fire_plate_pic_address);

    setPixmap(_pic.scaled(2*_r, 2*_r));
    setPos(level->width()/2 - _r, level->height() - _excess);
}

QPixmap Plate::image() {
    return (level->mode_name() == Fire) ? _fire_pic : _pic;
}

void Plate::update_pixmap() {
    setPixmap(image().scaled(2*_r, 2*_r));
}

void Plate::resize_length(double d) {
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

    if(len <= level->scaled(level->max_plate_length) && len >= level->scaled(level->min_plate_length)) {
        setX(x() - R);
        _r = R;
        update_pixmap();
    }

    if(!level->ball()->is_active())
        level->ball()->set_to_plate();
}

void Plate::resize_height(double d) {
    if(_excess + d <= level->scaled(level->max_plate_excess) && _excess + d >= level->scaled(level->min_plate_excess)) {
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
        update_pixmap();
    }

    if(!level->ball()->is_active())
        level->ball()->set_to_plate();
}

void Plate::move(double d) {
    if(x() + d >= 0 && x() + d <= scene()->width())
        setX(pos().x() + d);

    if(!level->ball()->is_active())
        level->ball()->set_to_plate();

    level->ball()->bounce_plate();
}

void Plate::set_on_fire(bool fire) {
    if(fire)
        setPixmap(QPixmap(level->fire_plate_pic_address).scaled(2*_r, 2*_r));
    else
        setPixmap(QPixmap(level->plate_pic_address).scaled(2*_r, 2*_r));
}

QPointF Plate::left() {
    return QPointF(x() - sqrt(_r*_r - (_r-_excess)*(_r-_excess)), pos().y() + _excess);
}

QPointF Plate::right() {
    return QPointF(x() + sqrt(_r*_r - (_r-_excess)*(_r-_excess)), pos().y() + _excess);
}

QPointF Plate::top() {
    return QPointF(x(), pos().y());
}

QPointF Plate::center() {
    return QPointF(x(), y());
}

double Plate::x() {
    return pos().x() + _r;
}

double Plate::y() {
    return pos().y() + _r;
}

double Plate::r() {
    return _r;
}

double Plate::excess() {
    return _excess;
}
