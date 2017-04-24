#include <QApplication>
#include <level.h>
#include <QDebug>

Level *level;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    level = new Level(2);
    level->load_scene();
    level->show();

    return a.exec();
}
