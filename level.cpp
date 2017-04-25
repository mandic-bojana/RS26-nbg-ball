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

Level::Level(QWidget *parent, int level) {
    setParent(parent);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setMouseTracking(true);
    setCursor(Qt::CrossCursor);

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
    _plate->setZValue(1);

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
    bricks_space = scaled(bricks_space);

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
    _scene->clear();
}

double Level::scaled(double x) {
    return x/1024*width();
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
    if(event->x() <= 5 || event->x() >= width() - 5 || event->y() <= 5 || event->y() >= height() - 5)
        setCursor(Qt::ForbiddenCursor);
    else
        setCursor(Qt::CrossCursor);

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
    if(event->key() == Qt::Key_Escape)
        parentWidget()->close();
    else if(_finished)
        return;
    else switch(event->key()) {
    case Qt::Key_Right:
        _plate->move(scaled(default_plate_move));
        break;
    case Qt::Key_Left:
        _plate->move(-scaled(default_plate_move));
        break;
    case Qt::Key_Up:
    case Qt::Key_Space: {
        Bullet* bullet = new Bullet();
        scene()->addItem(bullet);
        break;
    }
    case Qt::Key_A:
        _plate->resize_width(-scaled(default_plate_resize_width));
        break;
    case Qt::Key_D:
        _plate->resize_width(scaled(default_plate_resize_width));
        break;
    case Qt::Key_W:
        _plate->resize_height(scaled(default_plate_resize_height));
        break;
    case Qt::Key_S:
        _plate->resize_height(-scaled(default_plate_resize_height));
        break;
    }
}

const char* Level::plate_pic_address = ":/images/plate.png";
const char* Level::bullet_pic_address = ":/images/bullet.png";
const char* Level::ball_pic_address = ":/images/plate.png";
const char* Level::brick_pic_address = ":/images/brick.png";

const double Level::default_ball_radius = 10;
const double Level::default_ball_speed = 5;
const double Level::default_ball_angle = 1.2;
const double Level::default_ball_timer_interval = 13;
const double Level::default_bullet_radius = 7.5;
const double Level::default_bullet_speed = 10;
const double Level::default_bullet_timer_interval = 25;
const double Level::default_plate_excess = 40;
const double Level::default_plate_radius = 200;

const double Level::default_plate_move = 20;
const double Level::default_plate_resize_height = 10;
const double Level::default_plate_resize_width = 20;

const double Level::min_ball_timer_interval = 7;
const double Level::max_plate_excess = 60;
const double Level::max_plate_length = 400;
const double Level::min_plate_excess = 20;
const double Level::min_plate_length = 150;
