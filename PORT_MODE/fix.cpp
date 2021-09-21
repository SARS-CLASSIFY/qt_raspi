#include "fix.h"
#include "ui_fix.h"
#include <camera.h>

#include <QDebug.h>
#include <QKeyEvent>
//font
#include <QCoreApplication>
#include <QStringList>
#include <QFontDatabase>
#include <QFont>

//gif
#include <QLabel>
#include <QMovie>
//page
#include <QStackedWidget>
#include <qwidget.h>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QKeyEvent>

#include <fix.h>
#include <mainwindow.h>

/*--------------------------------------------------------------------
 * 预作为相册界面（按键上下键切换相册，左右键切换界面）
 * -----------------------------------------------------------------*/


static int pic_num = 0;//图片切换序号


fix::fix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fix)
{
    ui->setupUi(this);

    //private
    window3_init();
    pic_set(ui->label_img,addre2);
}

fix::~fix()
{
    delete ui;
}


//personal

/*---------------------------------------------
 * 返回上一界面
 * ------------------------------------------*/
//void fix::change_to_back()
//{
//    camera *win2 = new camera;
//    this->hide();
//    win2->show();
//}



//page set

/*-----------------------------------------
 * 字体样式设置
 * ----------------------------------------*/
void fix::font3_setup(void)
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
        font.setPixelSize(80);//设置字体大小
        font.setBold(true);//斜体
    }

    //标签测试
    ui->word2->setFont(font);//主题
    ui->word2->setStyleSheet("background-color: rgb(0, 0, 0);font-size:50px;color:white");
    ui->word2->setText("photo blum");


}


/*------------------------------------------------
 * 界面3初始化函数
 * --------------------------------------------*/

void fix::window3_init()
{
//    this->setStyleSheet("#centralWidget{border-image:url(:/timg.jpg);}" //设置指定图片为背景
    this->setStyleSheet("#fix{background:rgba(0,0,0,1);}" //设置主界面背景透明度
                        "#bar1{background:rgba(255,128,0,1);}"
                        "#pushButton{border-image:url(:/icon/btn1.svg);}"
       );
    font3_setup();
}


/*------------------------------------------------
 * 图片设置功能（此处打算做一个相册功能，上下键切换）
 * ---------------------------------------------*/

void fix::pic_set(QLabel *label,QString fileaddress)
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
void fix::pic_change(int up_or_down)
{
    switch (pic_num) {
    case 0:
        pic_set(ui->label_img,addre1);
        break;
    case 1:
        pic_set(ui->label_img,addre2);
        break;
    case 2:
        pic_set(ui->label_img,addre3);
        break;
    case 3:
        pic_set(ui->label_img,addre4);
        break;
    case 4:
        pic_set(ui->label_img,addre5);
        break;
    default:
        pic_set(ui->label_img,addre1);
        break;
    }

    if(up_or_down==1){
         pic_num=(pic_num+1)%5;
    }
    else{
         pic_num=(pic_num+4)%5;
    }


}


/*-----------------------------------------------
 * 按键响应函数（调试使用）
 * -----------------------------------------------*/
//void fix::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    //判断ESC按键事件
//    case Qt::Key_Escape:
//        qDebug()<<"esc"<<endl;
//        break;
//    //del键用于退出 全屏调试使用
//    case Qt::Key_Delete:
//        QApplication* app;
//        app->quit();
//        break;
//    case Qt::Key_Left://按下左键
//        change_to_back();
//        break;
//    case Qt::Key_Right:
//        //change_to_next();
//        break;
//    case Qt::Key_Up:
//        pic_change(1);
//        break;
//    case Qt::Key_Down:
//        pic_change(0);
//        break;
//    default:
//        break;
//    }
//}
