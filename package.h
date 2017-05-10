#ifndef PACKAGE_H
#define PACKAGE_H

#include "fallingitem.h"

class Package : public FallingItem
{
public:
    Package(double x, double y, QGraphicsItem * parent = 0);
};

#endif // PACKAGE_H
