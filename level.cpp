#include "level.h"
#include <QBrush>
#include <QImage>
#include <QDebug>
#include "bullet.h"

using namespace std;

Level::Level(QWidget *parent) {
    setParent(parent);

    _scene = new QGraphicsScene();
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

    bricks_row = 15;
    bricks_column = 20;
    bricks_space = 0;

    double brick_width = (width() - bricks_space)/bricks_row - bricks_space;
    double brick_height = (height() - bricks_space)/bricks_column - bricks_space;

    for(int i = 2; i < bricks_row - 2; i++)
        for(int j = 3; j < 7; j++) {
            Brick* brick = new Brick(brick_width, brick_height, bricks_space + i * (brick_width + bricks_space), bricks_space + j * (brick_height + bricks_space));
            _scene->addItem(brick);
        }

    _ball = new Ball(this);
    _scene->addItem(_ball);
    setMouseTracking(true);
    setCursor(Qt::BlankCursor);
    _ball->activate();
}

Level::~Level() {
    //delete _scene;
    delete _plate;
}

Plate *Level::plate() {
    return _plate;
}

void Level::mouseMoveEvent(QMouseEvent *event) {
    _plate->move(event->x() - _plate->x());
}

void Level::mousePressEvent(QMouseEvent *event) {
    Bullet* bullet=new Bullet();
    bullet->setPos(_plate->top());
    _scene->addItem(bullet);
}

const char* Level::plate_pic_address = ":/images/plate.png";
const char* Level::bullet_pic_address = ":/images/bullet.png";
const char* Level::ball_pic_address = ":/images/plate.png";
const char* Level::brick_pic_address = ":/images/brick.png";
