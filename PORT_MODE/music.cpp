#include "music.h"
#include "ui_music.h"



//font
#include <QCoreApplication>
#include <QStringList>
#include <QFontDatabase>
#include <QFont>




int pic_num = 0;//图片切换序号

music::music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music)
{
    ui->setupUi(this);

    play_init();
    this->setWindowFlags(Qt::X11BypassWindowManagerHint  | Qt::FramelessWindowHint);
    this->move(122, 162);//窗口移动
    qmovie_setup();

    isPlay = false;//默认不播放
    ui->icon->hide();

}

music::~music()
{
    delete ui;



}

//personal



/*-----------------------------------------
 * 字体样式设置
 * ----------------------------------------*/
void music::font_setup(void)
{
    QStringList m_fontList;
    QFont font;
    m_fontList.clear();

    int lcdFontId = QFontDatabase::addApplicationFont(":/ALiHanYiZhiNengHeiTi-2.ttf"); // 从source资源文件
    // int lcdFontId = QFontDatabase::addApplicationFont(dir + "/fonts/DS-DIGI.ttf"); //从外部资源文件
    if (lcdFontId != -1) // -1为加载失败
    {
        m_fontList << QFontDatabase::applicationFontFamilies(lcdFontId);
    }
    if (!m_fontList.isEmpty())
    {

        font.setFamily(m_fontList.at(0));//设置字体样式
        font.setPixelSize(50);//设置字体大小
        font.setBold(true);//斜体
    }

    //标签测试
    ui->word2->setFont(font);//主题
    ui->word2->setStyleSheet("background-color: rgb(0, 0, 0);font-size:35px;color:white");
//    ui->word2->setText("");


}




/*---------------------------------------------------------------------------
 * gif动图设置
-----------------------------------------------------------------------------------*/
void music::qmovie_setup(void)
{
    showGif = new QMovie(":/resourses/music/3.gif");
    //设置适应Qlabel大小
    QSize my_size = ui->gif->size();
    showGif->setScaledSize(my_size);

    ui->gif->setMovie(showGif);
    showGif->start();
}


void music::play_init()
{



    //    this->setStyleSheet("#centralWidget{border-image:url(:/timg.jpg);}" //设置指定图片为背景
        this->setStyleSheet("#music{background:rgba(0,0,0,1);}" //设置主界面背景透明度
                            "#bar1{background:rgba(255,128,0,1);}"
           );
        font_setup();
        ui->word2->setStyleSheet("background-color: rgb(0, 0, 0);font-size:35px;color:white");
        pic_set(ui->picture,addre1);


        playlist = new QMediaPlaylist;
        playlist->addMedia(QUrl::fromLocalFile("J:/qt_raspi/qt_raspi/PORT_MODE/resourses/music/1.mp3"));
        playlist->addMedia(QUrl::fromLocalFile("J:/qt_raspi/qt_raspi/PORT_MODE/resourses/music/2.mp3"));
        playlist->addMedia(QUrl::fromLocalFile("J:/qt_raspi/qt_raspi/PORT_MODE/resourses/music/3.mp3"));
        playlist->setCurrentIndex(1);

        player = new QMediaPlayer;
        player->setPlaylist(playlist);


}


/* ------------------------------------------------------
 *  下一曲
 * ------------------------------------------------------*/
void music::on_nextSong_clicked()
{
    //如果播放列表为空，按钮不可用，直接返回
    if(playlist->isEmpty())
        return;
    //如果列表到尽头，则回到列表开头
    int currentIndex=playlist->currentIndex();
    if(++currentIndex==playlist->mediaCount()){
        currentIndex=0;
    }
    //设置当前的currentIndex
    playlist->setCurrentIndex(currentIndex);
    pic_follow(currentIndex);
    isPlay=true;
    player->play();
}


/* -----------------------------------------------------------------
 *  上一曲
 * ----------------------------------------------------------------*/
void music::on_firstSong_clicked()
{
    //播放列表为空，按钮不可用，直接返回
    if(playlist->isEmpty())
        return;
    //如果列表到开头，则停止播放，直接返回
    int currentIndex=playlist->currentIndex();

    if(--currentIndex<0){
        currentIndex=2;
    }

    playlist->setCurrentIndex(currentIndex);
    pic_follow(currentIndex);
    isPlay=true;
    player->play();

//    if(currentIndex==0){
//        isPlay=true;
//        pic_follow(currentIndex);
//        player->play();

//        return;
//    }
//    playlist->previous();

//    isPlay=true;
//    pic_follow(currentIndex);
//    player->play();
}

/* ------------------------------------------------------------------
 *  播放和暂停
 * ------------------------------------------------------------------*/
void music::play_status()
{
    //如果播放列表为空，按钮不可用，直接返回
    if(playlist->isEmpty())
        return;
    isPlay=!isPlay;

    if(isPlay)
    {   player->pause();

        ui->icon->hide();
        ui->icon2->show();
//        ui->play->setIcon(QIcon(":/images/play.png"));// 暂停时候显示播放图标
//        ui->play->setToolTip(tr("暂停"));
    }
    else
    {   player->play();

        ui->icon->show();
        ui->icon2->hide();
//        ui->play->setIcon(QIcon(":/images/pause.png"));// 播放时候显示暂停图标
//        ui->play->setToolTip(tr("播放"));
    }
}

/*------------------------------------------------
 * 图片设置功能（此处打算做一个相册功能，上下键切换）
 * ---------------------------------------------*/

void music::pic_set(QLabel *label,QString fileaddress)
{
    QImage *img=new QImage; //新建一个image对象



    img->load(fileaddress); //将图像资源载入对象img，注意路径，可点进图片右键复制路径

    img->scaled(label->size(), Qt::KeepAspectRatio);
    label->setScaledContents(true);
    label->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
}

/*-------------------------------------------------
 * 图片切换功能（上下键控制上一张和下一张）
 * ----------------------------------------------*/
void music::pic_change(int up_or_down)
{
    switch (pic_num) {
    case 0:
        pic_set(ui->picture,addre1);
        break;
    case 1:
        pic_set(ui->picture,addre2);
        break;
    case 2:
        pic_set(ui->picture,addre3);
        break;
    default:
        pic_set(ui->picture,addre1);
        break;
    }

    if(up_or_down==1){
         pic_num=(pic_num+1)%4;
    }
    else{
         pic_num=(pic_num+3)%4;
    }


}


/*-------------------------------------------------
 * 图片切换功能3
 * ----------------------------------------------*/
void music::pic_follow(int num)
{
    switch (num) {
    case 0:
        pic_set(ui->picture,addre1);
        break;
    case 1:
        pic_set(ui->picture,addre2);
        break;
    case 2:
        pic_set(ui->picture,addre3);
        break;
    default:
        pic_set(ui->picture,addre1);
        break;
    }
}




//控制部分
//void music::on_pushButton_clicked()
//{
//    on_nextSong_clicked();
//}


//void music::on_pushButton_2_clicked()
//{
//    on_firstSong_clicked();
//}

//void music::on_pushButton_3_clicked()
//{
//    play_status();
//}
