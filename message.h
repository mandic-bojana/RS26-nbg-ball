#ifndef MESSAGE_H
#define MESSAGE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>


class Message: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Message(const QString &picture_address, QGraphicsItem * parent = 0);
    ~Message();

    QTimer* timer();

public slots:
    void disappear();

private:
    QTimer* _timer;
};

#endif // MESSAGE_H
