#ifndef MODE_H
#define MODE_H

#include "message.h"
#include <QTimer>

class Mode: public QObject
{
    Q_OBJECT
public:
    Mode(const QString &message_pic_addr, const QString& falling_item_pic_addr);

public slots:
    void item_rain();
    void stop_initializing_effect();

protected:
    Message* message;
    QString falling_item_pic_addr;
    QTimer* item_rain_timer;
};

class WinterMode : public Mode
{
    Q_OBJECT
public:
    WinterMode();

public slots:
    void freeze();
};

class SamuraiMode : public Mode
{
    Q_OBJECT
public:
    SamuraiMode();
};

class FireMode : public Mode
{
    Q_OBJECT
public:
    FireMode();
};

#endif
