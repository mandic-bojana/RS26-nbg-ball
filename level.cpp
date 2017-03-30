#include "level.h"
#include <QBrush>
#include <QImage>
#include <QDebug>
#include "bullet.h"

Level::Level(QWidget *parent) {
    setParent(parent);

    _scene = new QGraphicsScene;
    setScene(_scene);

    _scene->setSceneRect(0, 0, 800, 600);
  //_scene->setBackgroundBrush(QBrush(QImage(":/images/space.jpg")));

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    _plate = new Plate(this);
    _plate->setFlag(QGraphicsItem::ItemIsFocusable);
    _plate->setFocus();
    _scene->addItem(_plate);

    _ball=new Ball(this);
    _scene->addItem(_ball);
    setMouseTracking(true);
}

Level::~Level() {
    //delete _scene;
    delete _plate;
}


Plate *Level::plate()
{
    return _plate;
}

void Level::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<event->x();
    _plate->move(event->x() - _plate->x());
}

void Level::mousePressEvent(QMouseEvent *event)
{
    Bullet* bullet=new Bullet();
    bullet->setPos(_plate->x(), _plate->y() - _plate->r());
    _scene->addItem(bullet);
}

const char* Level::plate_pic_address = ":/images/plate.png";
const char* Level::ball_pic_address = ":/images/plate.png";
