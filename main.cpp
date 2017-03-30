#include <QApplication>
#include <level.h>

Level *level;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    level = new Level();
    level->show();

    return a.exec();
}
