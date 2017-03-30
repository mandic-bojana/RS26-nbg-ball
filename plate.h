#ifndef PLATE_H
#define PLATE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QKeyEvent>

class Plate: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Plate(QGraphicsView *view, QGraphicsItem* parent = 0);
    double x();
    double y();
    double r();
    double excess();
    void resize_height(double x);
    void resize_width(double x);

public slots:
    void keyPressEvent(QKeyEvent *event);

private:
    double _excess;
    double _r;
    const static double max_excess = 100;
    const static double max_length = 400;
    const static double min_excess = 20;
    const static double min_length = 50;
};

#endif // PLATE_H
