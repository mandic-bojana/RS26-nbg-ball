#include "package.h"
#include "level.h"
#include <QDebug>

extern Level* level;

Package::Package(const QString &pic_addr, double x, double y, QGraphicsItem *parent)
    : FallingItem(pic_addr, x, y, level->scaled(level->default_package_length), M_PI/2, parent) { }


void Package::move() {
    if(collidesWithItem(level->plate())) {
        upgrade();
        destroy();
    }

    else
        FallingItem::move();
}

IncreasePlateLength::IncreasePlateLength(double x, double y, QGraphicsItem *parent)
    : Package(level->increase_plate_length_pic_address, x, y, parent) { }

DecreasePlateLength::DecreasePlateLength(double x, double y, QGraphicsItem *parent)
    : Package(level->decrease_plate_length_pic_address, x, y, parent) { }

IncreasePlateWidth::IncreasePlateWidth(double x, double y, QGraphicsItem *parent)
    : Package(level->increase_plate_height_pic_address, x, y, parent) { }

DecreasePlateWidth::DecreasePlateWidth(double x, double y, QGraphicsItem *parent)
    : Package(level->decrease_plate_height_pic_address, x, y, parent) { }

SamuraiModeActivate::SamuraiModeActivate(double x, double y, QGraphicsItem *parent)
    : Package(level->sushi_pic_address, x, y, parent) { }

WinterModeActivate::WinterModeActivate(double x, double y, QGraphicsItem *parent)
    : Package(level->ice_cream_pic_address, x, y, parent) { }

FireModeActivate::FireModeActivate(double x, double y, QGraphicsItem *parent)
    : Package(level->pepper_pic_address, x, y, parent) { }

SpeedModeActivate::SpeedModeActivate(double x, double y, QGraphicsItem *parent)
    : Package(level->speed_candy_pic_address, x, y, parent) { }

DefaultModeActivate::DefaultModeActivate(double x, double y, QGraphicsItem *parent)
    : Package(level->package_pic_address, x, y, parent) { }

void IncreasePlateLength::upgrade() {
    level->plate()->resize_length(level->scaled(level->default_plate_resize_length));
}

void DecreasePlateLength::upgrade() {
    level->plate()->resize_length(-level->scaled(level->default_plate_resize_length));
}

void IncreasePlateWidth::upgrade() {
    level->plate()->resize_height(level->scaled(level->default_plate_resize_height));
}

void DecreasePlateWidth::upgrade() {
    level->plate()->resize_height(-level->scaled(level->default_plate_resize_height));
}

void SamuraiModeActivate::upgrade() {
    level->change_mode(Samurai);
}

void WinterModeActivate::upgrade() {
    level->change_mode(Winter);
}

void FireModeActivate::upgrade() {
    level->change_mode(Fire);
}

void SpeedModeActivate::upgrade() {
    level->change_mode(Speed);
}

void DefaultModeActivate::upgrade() {
    level->change_mode(Default);
}
