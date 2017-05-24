#include "score.h"
#include "ui_score.h"
#include "level.h"

extern Level *level;

Score::Score(QWidget *parent) :
    QDialog(parent), ui(new Ui::Score) {

    _url = new QUrl("ftp://files.000webhost.com/scoreboard.nbg");
    _url->setUserName("simkers");
    _url->setPassword("3EAM2Q4d");

    _file = nullptr;
    _scoreboard = nullptr;
    _download_reply = nullptr;
    _upload_reply = nullptr;
    _manager = nullptr;
    _message = nullptr;
    ui->setupUi(this);
}

Score::~Score() {
    delete _file;
    delete _scoreboard;
    delete _download_reply;
    delete _upload_reply;
    delete _manager;
    delete _message;
    delete _url;
    delete ui;
}

void Score::on_buttonBox_accepted() {
    _name = new QString(ui->lineEdit->text());
    _time = level->get_time();

    ui->label->setText("Download");
    ui->progressBar->setEnabled(true);
    download();
}

void Score::download() {
    _manager = new QNetworkAccessManager(this);
    _download_reply = _manager->get(QNetworkRequest(*_url));

    QObject::connect(_download_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(_download_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progress(qint64, qint64)));
    QObject::connect(_download_reply, SIGNAL(finished()), this, SLOT(download_finished()));
}

void Score::error(QNetworkReply::NetworkError x) {
    _message = new QMessageBox;
    _message->setText("Pao alas. -_ -\n" + x);
    _message->show();
}

void Score::progress(qint64 x, qint64 y) {
    ui->progressBar->setValue((double)x/y*100);
}

void Score::download_finished() {
    char s[1000];
    _download_reply->read(s, 1000);
    QString file(s);

    _scoreboard = new QStringList(file.split("\n"));
    QStringList::iterator it = _scoreboard->begin();
    QStringList::iterator it_end = _scoreboard->end();

    for(; it != it_end; it++) {
        QStringList name = (*it).split("\\");
        if(_time < name[1].toInt()) {
            _scoreboard->insert(it, *_name + "\\" + QString::number(_time));
            break;
        }
    }
    if(it == it_end)
        _scoreboard->insert(it, *_name + QString::number(_time));

    ui->label->setText("Upload");
    upload();
}

void Score::upload() {
    _file = new QFile("scoreboard.nbg");
    _file->open(QIODevice::WriteOnly);

    QStringList::iterator it = _scoreboard->begin();
    QStringList::iterator it_end = _scoreboard->end();

    for(; it != it_end; it++) {
        QString line = *it + "\n";
        _file->write(line.toLatin1().data());
    }
    _file->close();

    _file->open(QIODevice::ReadOnly);
    _upload_reply = _manager->put(QNetworkRequest(*_url), _file->readAll());

    QObject::connect(_upload_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(_upload_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progress(qint64, qint64)));
    QObject::connect(_upload_reply, SIGNAL(finished()), this, SLOT(upload_finished()));
}

void Score::upload_finished() {
    _file->close();
    level->scoreboard_show();
    accept();
}
