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
    Plate(QGraphicsView *view, QGraphicsItem* parent = 0);
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

public slots:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    double _excess;
    double _r;
    static const double max_excess;
    static const double max_length;
    static const double min_excess;
    static const double min_length;
};

#endif // PLATE_H
