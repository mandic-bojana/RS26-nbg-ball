#include "mode.h"
#include "level.h"
#include "fallingitem.h"
#include <QDebug>
#include <algorithm>

extern Level *level;

Mode::Mode(const QString &message_pic_addr, const QString &falling_item_pic_addr)
    : falling_item_pic_addr(falling_item_pic_addr) {
    message = new Message(message_pic_addr);

    item_rain_timer = new QTimer();
    item_rain_timer->start(70);
    QObject::connect(item_rain_timer, SIGNAL(timeout()), this, SLOT(item_rain()));
    QObject::connect(message->timer(), SIGNAL(destroyed(QObject*)), this, SLOT(stop_initializing_effect()));
}

void Mode::item_rain() {
    new FallingItem(falling_item_pic_addr, qrand() % int(level->scene()->width()), 0, level->scaled(level->default_fallingitem_length));
}

void Mode::stop_initializing_effect() {
    item_rain_timer->stop();
    delete item_rain_timer;
}

SamuraiMode::SamuraiMode()
    : Mode(level->samurai_text_pic_address, level->flower_pic_address) { }

WinterMode::WinterMode()
    : Mode(level->winter_text_pic_address, level->snowflake_pic_address) {

    QList<Brick*> bricks = level->bricks();
    QList<Brick*>::iterator it = bricks.begin();
    QList<Brick*>::iterator it_end = bricks.end();
    for(; it != it_end; it++)
        (*it)->create_ice();
    QObject::connect(message->timer(), SIGNAL(timeout()), this, SLOT(freeze()));
}

void WinterMode::freeze() {
    QList<Brick*> bricks = level->bricks();
    QList<Brick*>::iterator it = bricks.begin();
    QList<Brick*>::iterator it_end = bricks.end();
    for(; it != it_end; it++)
        (*it)->freeze();
}
