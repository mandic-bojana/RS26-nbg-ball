#include "level.h"
#include "bullet.h"
#include <QBrush>
#include <QImage>
#include <QDebug>
#include <QIODevice>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include <cstddef>
#include <iostream>
#include "mode.h"

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
    _mode = nullptr;

    _scene = new QGraphicsScene();
    setScene(_scene);

    _scene->setSceneRect(0, 0, width(), height());
    _scene->setBackgroundBrush(QBrush(QImage(level_addr(_level, ".png")).scaledToWidth(width())));

    _plate = new Plate();
    _plate->setFlag(QGraphicsItem::ItemIsFocusable);
    _scene->addItem(_plate);
    _plate->setZValue(2);

    _ball = new Ball();
    _scene->addItem(_ball);
    _ball->setZValue(1);

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
            Brick* brick = NULL;
            switch (line[j]) {
            case 'y':
                brick = new YellowBrick(brick_width, brick_height, bricks_space + j * (brick_width + bricks_space), bricks_space + i * (brick_height + bricks_space));
                break;
            case 'r':
                brick = new RedBrick(brick_width, brick_height, bricks_space + j * (brick_width + bricks_space), bricks_space + i * (brick_height + bricks_space));
                break;
            case 'g':
                brick = new GreenBrick(brick_width, brick_height, bricks_space + j * (brick_width + bricks_space), bricks_space + i * (brick_height + bricks_space));
                break;
            case 'b':
                brick = new BlueBrick(brick_width, brick_height, bricks_space + j * (brick_width + bricks_space), bricks_space + i * (brick_height + bricks_space));
                break;
            }
            if(brick)
                _scene->addItem(brick);
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

QList<Brick*> Level::bricks() {
    QList<Brick*> bricks;
    QList<QGraphicsItem*> items = scene()->items();
    QList<QGraphicsItem*>::iterator it = items.begin();
    QList<QGraphicsItem*>::iterator it_end = items.end();
    for(; it != it_end; it++)
        if(dynamic_cast<Brick*>(*it))
            bricks.append((Brick*)*it);
    return bricks;
}

void Level::unfreeze() {
    QList<Brick*> brcs = bricks();
    QList<Brick*>::iterator it = brcs.begin();
    QList<Brick*>::iterator it_end = brcs.end();
    for(; it != it_end; it++)
        (*it)->unfreeze();
}

bool Level::solved() {
    return bricks().empty();
}

void Level::clean() {
    delete _mode;
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
    else if(mode_name() == Fire) {
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
        _plate->resize_length(-scaled(default_plate_resize_length));
        break;
    case Qt::Key_D:
        _plate->resize_length(scaled(default_plate_resize_length));
        break;
    case Qt::Key_W:
        _plate->resize_height(scaled(default_plate_resize_height));
        break;
    case Qt::Key_S:
        _plate->resize_height(-scaled(default_plate_resize_height));
        break;

    case Qt::Key_Z:
        change_mode(Fire);
        break;
    case Qt::Key_X:
        change_mode(Winter);
        break;
    case Qt::Key_C:
        change_mode(Samurai);
        break;
    case Qt::Key_V:
        change_mode(Speed);
        break;
    case Qt::Key_B:
        change_mode(Default);
        break;
    }
}

ModeName Level::mode_name() {
    if(!_mode)
        return Default;
    if (typeid(*_mode) == typeid(WinterMode))
        return Winter;
    if (typeid(*_mode) == typeid(FireMode))
        return Fire;
    if (typeid(*_mode) == typeid(SamuraiMode))
        return Samurai;
    if (typeid(*_mode) == typeid(SpeedMode))
        return Speed;
    return Default;
}

void Level::change_mode(ModeName mode_name) {
    _mode->reset();
    delete _mode;
    switch (mode_name) {
    case Winter:
        _mode = new WinterMode();
        break;
    case Fire:
        _mode = new FireMode();
        break;
    case Samurai:
        _mode = new SamuraiMode();
        break;
    case Speed:
        _mode = new SpeedMode();
        break;
    case Default:
    default:
        _mode = nullptr;
        unfreeze();
        break;
    }
    _ball->move_eyes();
}

const char* Level::plate_pic_address = ":/images/plate.png";
const char* Level::fire_plate_pic_address = ":/images/fire_plate.png";
const char* Level::package_pic_address = ":/images/package.png";
const char* Level::bullet_pic_address = ":images/bullet.png";

const char* Level::yellow_brick_pic_address = ":/images/yellow_brick.png";
const char* Level::red_brick_pic_address = ":/images/red_brick.png";
const char* Level::green_brick_pic_address = ":/images/green_brick.png";
const char* Level::blue_brick_pic_address = ":/images/blue_brick.png";

const char* Level::catface_pic_address = ":/images/catface.png";
const char* Level::catface_up_pic_address = ":/images/catface_up.png";
const char* Level::catface_down_pic_address = ":/images/catface_down.png";
const char* Level::catface_left_pic_address = ":/images/catface_left.png";
const char* Level::catface_blink_pic_address = ":/images/catface_blink.png";
const char* Level::catface_right_pic_address = ":/images/catface_right.png";
const char* Level::catface_samurai_pic_address = ":/images/catface_samurai.png";
const char* Level::catface_samurai_left_pic_address = ":/images/catface_samurai_left.png";
const char* Level::catface_samurai_right_pic_address = ":/images/catface_samurai_right.png";
const char* Level::catface_speed_pic_address = ":/images/catface_speed.png";
const char* Level::catface_speed_blink_pic_address = ":/images/catface_speed_blink.png";

const char* Level::snowflake_pic_address = ":/images/snowflake.png";
const char* Level::speed_pic_address = ":/images/speed.png";
const char* Level::flower_pic_address = ":/images/flower.png";
const char* Level::winter_text_pic_address = ":/images/winter_text.png";
const char* Level::samurai_text_pic_address = ":/images/samurai_text.png";
const char* Level::fire_text_pic_address = ":/images/fire_text.png";
const char* Level::speed_text_pic_address = ":/images/speed_text.png";

const char* Level::increase_plate_length_pic_address = ":/images/plate_increase_length.png";
const char* Level::decrease_plate_length_pic_address = ":/images/plate_decrease_length.png";
const char* Level::increase_plate_height_pic_address = ":/images/plate_increase_height.png";
const char* Level::decrease_plate_height_pic_address = ":/images/plate_decrease_height.png";

const char* Level::ice_cream_pic_address = ":/images/ice_cream.png";
const char* Level::sushi_pic_address = ":/images/sushi.png";
const char* Level::speed_candy_pic_address = ":/images/speed_candy.png";
const char* Level::pepper_pic_address = ":/images/pepper.png";

const double Level::default_ball_timer_interval = 7;
const double Level::default_ball_angle = 1.2;
const double Level::default_ball_radius = 20;
const double Level::default_ball_speed = 3;
const double Level::default_speed_ball_radius = 8;
const double Level::default_speed_ball_speed = 4.2;
const double Level::default_bullet_radius = 5.5;
const double Level::default_bullet_speed = 10;
const double Level::default_bullet_timer_interval = 25;
const double Level::default_plate_excess = 40;
const double Level::default_plate_radius = 90;

const double Level::default_plate_move = 20;
const double Level::default_plate_resize_height = 10;
const double Level::default_plate_resize_length = 20;

const double Level::default_package_length = 45;

const double Level::default_fallingitem_timer_interval = 25;
const double Level::default_fallingitem_length = 15;
const double Level::default_fallingitem_speed = 8;

const double Level::default_message_width = 400;
const double Level::default_message_height = 200;

const double Level::min_ball_timer_interval = 5;
const double Level::max_plate_excess = 60;
const double Level::max_plate_length = 400;
const double Level::min_plate_excess = 20;
const double Level::min_plate_length = 80;
