#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include "plate.h"
#include "brick.h"
#include "ball.h"
#include "mode.h"
#include "score.h"

using namespace std;

enum ModeName {Default, Winter, Samurai, Fire, Speed};

class Level : public QGraphicsView
{
public:
    Level(QWidget *parent = 0, int level = 0);
    ~Level();

    Plate* plate();
    Ball* ball();
    Mode* mode();
    QList<Brick*> bricks();

    ModeName mode_name();
    void change_mode(ModeName mode_name);

    void load_scene();
    void load_bricks();

    void add_time(int time);
    int get_time();

    void pause(bool paused = true);
    bool paused();
    bool solved();
    void clean();
    void next_level();
    void repeat_level();
    void the_end();
    void scoreboard_show();

    void unfreeze();

    double scaled(double x);

    static const char* plate_pic_address;
    static const char* package_pic_address;
    static const char* fire_plate_pic_address;
    static const char* bullet_pic_address;

    static const char* yellow_brick_pic_address;
    static const char* red_brick_pic_address;
    static const char* green_brick_pic_address;
    static const char* blue_brick_pic_address;
    static const char* old_brick_pic_address;

    static const char* catface_pic_address;
    static const char* catface_up_pic_address;
    static const char* catface_down_pic_address;
    static const char* catface_left_pic_address;
    static const char* catface_right_pic_address;
    static const char* catface_blink_pic_address;
    static const char* catface_samurai_pic_address;
    static const char* catface_samurai_left_pic_address;
    static const char* catface_samurai_right_pic_address;
    static const char* catface_speed_pic_address;
    static const char* catface_speed_blink_pic_address;
    static const char* snowflake_pic_address;
    static const char* speed_pic_address;
    static const char* flower_pic_address;
    static const char* flame_pic_address;
    static const char* winter_text_pic_address;
    static const char* samurai_text_pic_address;
    static const char* fire_text_pic_address;
    static const char* speed_text_pic_address;
    static const char* cap_pic_address;

    static const char* increase_plate_length_pic_address;
    static const char* decrease_plate_length_pic_address;
    static const char* increase_plate_height_pic_address;
    static const char* decrease_plate_height_pic_address;

    static const char* ice_cream_pic_address;
    static const char* speed_candy_pic_address;
    static const char* pepper_pic_address;
    static const char* sushi_pic_address;

    static const char* decrease_sound;
    static const char* increase_sound;
    static const char* hit_sound;
    static const char* sword_sound;
    static const char* fire_sound;
    static const char* gunshot_sound;
    static const char* samurai_sound;
    static const char* speed_sound;
    static const char* winter_sound;

    static const double default_ball_radius;
    static const double default_ball_speed;
    static const double default_ball_angle;
    static const double default_ball_timer_interval;
    static const double default_ball_acceleration;
    static const double default_speed_ball_radius;
    static const double default_speed_ball_speed;
    static const double default_bullet_radius;
    static const double default_bullet_speed;
    static const double default_bullet_timer_interval;
    static const double default_plate_excess;
    static const double default_plate_radius;
    static const double default_plate_move;
    static const double default_plate_resize_height;
    static const double default_plate_resize_length;

    static const double default_package_length;

    static const double default_fallingitem_timer_interval;
    static const double default_fallingitem_length;
    static const double default_fallingitem_speed;

    static const double default_message_width;
    static const double default_message_height;

    static const double max_ball_acceleration;
    static const double min_ball_angle;
    static const double max_plate_excess;
    static const double max_plate_length;
    static const double min_plate_excess;
    static const double min_plate_length;

    static const char* scoreboard_file_name;

public slots:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsScene *_scene;

    QMediaPlaylist *_playlist;
    QMediaPlayer *_player;
    Score *_scorebox;
    QGraphicsTextItem *_timer;
    int _time;
    QGraphicsTextItem *_scoreboard;

    Mode* _mode;
    Plate *_plate;
    Ball *_ball;

    int _level;
    bool _finished;
    bool _paused;

    int bricks_row;
    int bricks_column;
    int bricks_space;

    QString level_addr(int i, QString extension = ".nbg", QString prefix = "", bool qrc = false);
    QString two_chars(int num);
    QString format(int time);
};

#endif // LEVEL_H
