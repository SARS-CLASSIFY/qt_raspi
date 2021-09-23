#include "music.h"
#include "ui_music.h"



music::music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music)
{
    ui->setupUi(this);

    play_init();
}

music::~music()
{
    delete ui;


    this->setWindowFlags(Qt::X11BypassWindowManagerHint  | Qt::FramelessWindowHint);
    this->move(122, 162);//窗口移动

    play_init();
}

//personal

void music::play_init()
{
        playlist = new QMediaPlaylist;
        playlist->addMedia(QUrl::fromLocalFile(":/resourses/music/In the End - Linkin Park.mp3"));
        playlist->addMedia(QUrl::fromLocalFile("/resourses/music/Toby Fox - Undertale.mp3"));
        playlist->addMedia(QUrl::fromLocalFile("/resourses/music/Yellow (Acoustic Version From Jo Whiley's Lunchtime Social) - Coldplay.mp3"));
        playlist->setCurrentIndex(1);

        player = new QMediaPlayer;
        player->setPlaylist(playlist);

        player->play();
}
