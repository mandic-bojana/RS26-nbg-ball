#ifndef MODE_H
#define MODE_H

#include "message.h"
#include <QTimer>
#include <QSound>

class Mode: public QObject
{
    Q_OBJECT
public:
    Mode(const QString &message_pic_addr, const QString& falling_item_pic_addr);
    ~Mode();

    void reset();
    virtual void play_sound() = 0;

public slots:
    void item_rain();
    void stop_initializing_effect();

protected:
    Message* message;
    QString falling_item_pic_addr;
    QTimer* item_rain_timer;
    QSound* sound;
};

class WinterMode : public Mode
{
    Q_OBJECT
public:
    WinterMode();
    void play_sound();

public slots:
    void freeze();
};

class SamuraiMode : public Mode
{
    Q_OBJECT
public:
    SamuraiMode();
    void play_sound();
};

class FireMode : public Mode
{
    Q_OBJECT
public:
    FireMode();
    void play_sound();
};

class SpeedMode : public Mode
{
    Q_OBJECT
public:
    SpeedMode();
    void play_sound();
};

#endif // MODE_H
