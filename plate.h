#ifndef PLATE_H
#define PLATE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>

class Plate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Plate(QGraphicsItem* parent = 0);
    double x();
    double y();
    double r();
    double excess();
    void resize_height(double d);
    void resize_length(double d);
    void move(double d);
    void set_on_fire(bool fire);
    QPointF left();
    QPointF right();
    QPointF top();
    QPointF center();

    QPixmap image();
    void update_pixmap();

private:
    QPixmap _pic;
    QPixmap _fire_pic;
    double _excess;
    double _r;
};

#endif // PLATE_H
