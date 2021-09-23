#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>

//音频播放
#include <QMediaPlayer>
#include <QMediaPlaylist>
namespace Ui {
class music;
}

class music : public QWidget
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = 0);
    ~music();

private:
    Ui::music *ui;

    //player
    QMediaPlayer* player;
    QMediaPlaylist *playlist;

private slots:
    void play_init();

};

#endif // MUSIC_H
