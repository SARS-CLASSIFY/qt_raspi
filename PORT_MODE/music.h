#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>


#include <qlabel.h>
//音频播放
#include <QMediaPlayer>
#include <QMediaPlaylist>



//gif
#include <QLabel>
#include <QMovie>

namespace Ui {
class music;
}

class music : public QWidget
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = 0);

    void on_nextSong_clicked();
    void on_firstSong_clicked();
    void play_status();

    ~music();

private:
    Ui::music *ui;

    //player
    bool isPlay;
    QMediaPlayer* player;
    QMediaPlaylist *playlist;



    //图片路径
    QString addre1 = ":/resourses/music/1.jpeg";
    QString addre2 = ":/resourses/music/2.jpeg";
    QString addre3 = ":/resourses/music/3.jpeg";
    //动态图片
    QMovie *showGif;

private slots:
    void play_init();


    void pic_change(int up_or_down);
    void pic_set(QLabel *label,QString fileaddress);
    void pic_follow(int num);
    void font_setup(void);

    void qmovie_setup(void);

//    void on_pushButton_clicked();
//    void on_pushButton_2_clicked();
//    void on_pushButton_3_clicked();
};

#endif // MUSIC_H
