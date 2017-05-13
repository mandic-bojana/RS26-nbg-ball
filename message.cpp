#include "message.h"
#include "level.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <math.h>
#include <typeinfo>

extern Level *level;

Message::Message(const QString& picture_address, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent) {

    setPixmap(QPixmap(picture_address).scaled(level->scaled(level->default_message_width),
                                              level->scaled(level->default_message_height)));

    setOpacity(1);
    setPos(level->scene()->width() / 2 - level->scaled(level->default_message_width) / 2,
           level->scene()->height() / 5 * 2 - level->scaled(level->default_message_height) / 2);

    level->scene()->addItem(this);

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(disappear()));
    _timer->start(30);
}

Message::~Message() {
    _timer->stop();
    delete _timer;
    scene()->removeItem(this);
}

void Message::disappear() {
    setOpacity(opacity() - 0.01);
    if(opacity() <= 0)
        delete this;
}

QTimer *Message::timer() {
    return _timer;
}




