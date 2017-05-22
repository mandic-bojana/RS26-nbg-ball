#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
#include <math.h>
#include "brick.h"

class Ball: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ball(QGraphicsItem* parent = 0);
    ~Ball();

    void bounce(double alpha);
    void bounce_point(QPointF point);
    void bounce_point(double px, double py);
    void bounce_vertical();
    void bounce_horizontal();
    bool bounce_brick(Brick* brick);
    void bounce_plate();

    double angle_to(QPointF P);

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
    double speed();

    bool is_active();
    void activate(bool active = true);
    void set_to_plate();

    void blink();

    void reset();
    void reset_acceleration();
    void set_speed_mode();

public slots:
    void move();    
    void move_eyes();
    void set_cap();
    void remove_cap();

private:
    double _interval;
    double _r;
    double _speed_r;
    double _angle;
    double _speed;
    double _speed_speed;
    double _acceleration;
    bool _active;
    QTimer *_timer;
    QTimer *_eyes_timer;
    QSoundEffect * _sound;
    QVector<QPixmap> catface_images;
    QVector<QPixmap> catface_samurai_images;
    QPixmap catface_blink_image;
    QPixmap catface_speed_image;
    QPixmap catface_speed_blink_image;
    QGraphicsPixmapItem * _cap;
};

#endif // BALL_H
