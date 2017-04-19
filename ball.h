#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <math.h>


class Ball: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ball(QGraphicsView *view, QGraphicsItem *parent = 0);
    ~Ball();

    void bounce(double alpha);
    void bounce_point(QPointF point);
    void bounce_point(double px, double py);
    void bounce_vertical();
    void bounce_horizontal();

    bool goes_to(double px, double py);
    bool goes_to(QPointF P);
    bool goes_up();
    bool goes_down();
    bool goes_right();
    bool goes_left();

    QPointF C();
    double x();
    double y();
    double r();

public slots:
    void move();

private:
    double interval;
    double _r;
    double angle;
    double speed;
    QTimer *_timer;
};

#endif // BALL_H
