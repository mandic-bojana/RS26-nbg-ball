#ifndef PACKAGE_H
#define PACKAGE_H

#include "fallingitem.h"

class Package : public FallingItem
{
public:
    Package(const QString& pic_addr, double x, double y, QGraphicsItem* parent = 0);
    virtual void upgrade() = 0;
    void move();
};

class IncreasePlateLength : public Package
{
public:
    IncreasePlateLength(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

class DecreasePlateLength : public Package
{
public:
    DecreasePlateLength(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

class IncreasePlateWidth : public Package
{
public:
    IncreasePlateWidth(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

class DecreasePlateWidth : public Package
{
public:
    DecreasePlateWidth(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

class SamuraiModeActivate : public Package
{
public:
    SamuraiModeActivate(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

class WinterModeActivate : public Package
{
public:
    WinterModeActivate(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

class FireModeActivate : public Package
{
public:
    FireModeActivate(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

class DefaultModeActivate : public Package
{
public:
    DefaultModeActivate(double x, double y, QGraphicsItem* parent = 0);
    void upgrade();
};

#endif // PACKAGE_H
