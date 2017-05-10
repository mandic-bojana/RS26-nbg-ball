#include "package.h"
#include "level.h"

extern Level* level;

Package::Package(double x, double y, QGraphicsItem *parent)
    : FallingItem(level->package_pic_address, x, y, level->scaled(level->default_package_length), M_PI/2, parent) { }

