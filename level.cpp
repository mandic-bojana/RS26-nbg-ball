#include "level.h"
#include "bullet.h"
#include <QBrush>
#include <QImage>
#include <QDebug>
#include <QIODevice>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>

#define MAXLEN 100
#define LEVELS_NO 5

using namespace std;

QString level_addr(int i, const char* extension = ".nbg") {
    QString addr(":/levels/");
    char no[3];
    sprintf(no, "%d\0", i);
    addr += QString(no);
    addr += QString(extension);
    return addr;
}

Level::Level(int level, int width, int height, QWidget *parent) {
    setParent(parent);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(width, height);

    setMouseTracking(true);
    setCursor(Qt::BlankCursor);

    _level = level;
}

void Level::load_scene() {
    _finished = false;

    _scene = new QGraphicsScene();
    setScene(_scene);

    _scene->setSceneRect(0, 0, width(), height());
    _scene->setBackgroundBrush(QBrush(QImage(level_addr(_level, ".png")).scaledToWidth(width())));

    _plate = new Plate();
    _plate->setFlag(QGraphicsItem::ItemIsFocusable);
    _scene->addItem(_plate);

    _ball = new Ball();
    _scene->addItem(_ball);

    load_bricks();
}

void Level::load_bricks() {
    QFile file(level_addr(_level));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    char line[MAXLEN];
    file.readLine(line, MAXLEN);
    sscanf(line, "%d %d %d\n", &bricks_row, &bricks_column, &bricks_space);

    double brick_width = ((double)width() - bricks_space)/bricks_row - bricks_space;
    double brick_height = ((double)2/3*height() - bricks_space)/bricks_column - bricks_space;

    for(int i = 0; i < bricks_column; i++) {
        file.readLine(line, MAXLEN);
        for(int j = 0; j < bricks_row && line[j] != '\0'; j++) {
            if (line[j] == 'r') {
                Brick* brick = new Brick(brick_width, brick_height, bricks_space + j * (brick_width + bricks_space), bricks_space + i * (brick_height + bricks_space));
                _scene->addItem(brick);
            }
        }
    }
    file.close();
}

Level::~Level() {
    clean();
}

Plate *Level::plate() {
    return _plate;
}

Ball *Level::ball() {
    return _ball;
}

bool Level::solved() {
    QList<QGraphicsItem*> items = scene()->items();
    QList<QGraphicsItem*>::iterator it = items.begin();
    QList<QGraphicsItem*>::iterator it_end = items.end();
    for(; it != it_end; it++)
        if(typeid(**it) == typeid(Brick))
            return false;
    return true;
}

void Level::clean() {
    _finished = true;

    scene()->removeItem(_plate);
    delete _plate;
    scene()->removeItem(_ball);
    delete _ball;

    QList<QGraphicsItem*> items = scene()->items();
    QList<QGraphicsItem*>::iterator it = items.begin();
    QList<QGraphicsItem*>::iterator it_end = items.end();
    for(; it != it_end; it++)
        if(typeid(**it) == typeid(Bullet)) {
            Bullet* bullet = (Bullet*)*it;
            bullet->destroy();
        }
        else if(typeid(**it) == typeid(Brick)) {
            Brick* bullet = (Brick*)*it;
            bullet->hit();
        }
}

void Level::repeat_level() {
    load_scene();
}
void Level::next_level() {
    _level++;
    if(_level < LEVELS_NO)
        load_scene();
}

void Level::mouseMoveEvent(QMouseEvent *event) {
    if(!_finished) {
        _plate->move(event->x() - _plate->x());
        if(!_ball->is_active())
            _ball->setPos(event->x() - _ball->r(), _ball->pos().y());
    }
}

void Level::mousePressEvent(QMouseEvent *event) {
    if(_finished)
        next_level();
    else if(!_ball->is_active())
        _ball->activate();
    else {
        Bullet* bullet=new Bullet();
        _scene->addItem(bullet);
    }
}

void Level::keyPressEvent(QKeyEvent *event) {
    if(_finished)
        return;
    else if(event->key() == Qt::Key_Right)
        _plate->move(10);
    else if(event->key() == Qt::Key_Left)
        _plate->move(-10);
    else if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Space) {
        Bullet* bullet=new Bullet();
        scene()->addItem(bullet);
    }
    else if(event->key() == Qt::Key_A)
        _plate->resize_width(-10);
    else if(event->key() == Qt::Key_D)
        _plate->resize_width(10);
    else if(event->key() == Qt::Key_W)
        _plate->resize_height(10);
    else if(event->key() == Qt::Key_S)
        _plate->resize_height(-10);
}

const char* Level::plate_pic_address = ":/images/plate.png";
const char* Level::bullet_pic_address = ":/images/bullet.png";
const char* Level::ball_pic_address = ":/images/plate.png";
const char* Level::brick_pic_address = ":/images/brick.png";
