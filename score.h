#ifndef SCORE_H
#define SCORE_H

#include <QDialog>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

namespace Ui {
class Score;
}

class Score : public QDialog
{
    Q_OBJECT
public:
    explicit Score(QWidget *parent = 0);
    ~Score();

private slots:
    void on_buttonBox_accepted();

    void progress(qint64 x, qint64 y);
    void error(QNetworkReply::NetworkError x);
    void download_finished();
    void upload_finished();

    void on_buttonBox_rejected();

private:
    void download();
    void upload();
    void insert_result();
    void save_to_file();

    bool _upload;

    Ui::Score *ui;
    QMessageBox *_message;

    QUrl *_url;
    QNetworkReply *_download_reply;
    QNetworkReply *_upload_reply;
    QNetworkAccessManager *_manager;

    QFile *_file;

    QString *_name;
    int _time;
    QStringList *_scoreboard;
};

#endif // SCORE_H
