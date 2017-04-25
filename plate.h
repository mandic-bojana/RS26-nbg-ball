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
    void resize_width(double d);
    void move(double d);
    QPointF left();
    QPointF right();
    QPointF top();
    QPointF center();

private:
    double _excess;
    double _r;
};

#endif // PLATE_H
