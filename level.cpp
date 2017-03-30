#include "level.h"
#include <QBrush>
#include <QImage>
#include <QDebug>

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
}

Level::~Level() {
    //delete _scene;
    delete _plate;
}


Plate *Level::plate()
{
    return _plate;
}

