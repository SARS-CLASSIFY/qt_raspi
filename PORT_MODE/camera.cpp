#include "camera.h"
#include "ui_camera.h"
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

camera::camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
    window2_init();
}

camera::~camera()
{
    delete ui;
}

//personal


/*-----------------------------------------------
 * 按键响应函数（调试使用）
 * -----------------------------------------------*/
void camera::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    //判断ESC按键事件
    case Qt::Key_Escape:
        qDebug()<<"esc"<<endl;
        break;
    //del键用于退出 全屏调试使用
    case Qt::Key_Delete:
        QApplication* app;
        app->quit();
        break;
    case Qt::Key_Left://按下左键
        change_to_back();
        break;
    case Qt::Key_Right://按下左键
        change_to_next();
        break;
    default:
        break;
    }
}


/*--------------------------------------------
 * 切换到下一界面
 * ---------------------------------------------*/
void camera::change_to_next()
{
    fix *win3 = new fix;
    this->hide();
    win3->show();


}

/*-------------------------------------------------
 * 切换到下一界面
 * -----------------------------------------------*/
void camera::change_to_back()
{
    MainWindow*main = new MainWindow;
    this->hide();
    main->show();


}


/*---------------------------------------------------
 * 字体样式设置
 * ------------------------------------------------*/
void camera::font2_setup(void)
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
    ui->word->setFont(font);//主题
    ui->word->setStyleSheet("background-color: rgb(0, 0, 0);font-size:100px;color:white");
    ui->word->setText("camera");

//    ui->label->setFont(font);//日期
//    ui->label->setStyleSheet("background-color: rgb(0, 0, 0);font-size:20px;color:white");
//    ui->label->setText("星期日\n8月23日");


}

/*-----------------------------------------------------------
 * 界面2初始化
 * -------------------------------------------------------*/

void camera::window2_init()
{
//    this->setStyleSheet("#centralWidget{border-image:url(:/timg.jpg);}" //设置指定图片为背景
    this->setStyleSheet("#camera{background:rgba(0,0,0,1);}" //设置主界面背景透明度
                        "#label{border-image:url(:/icon/camera1.svg);}"
                        "#bar{background:rgba(255,128,0,1);}"
                        "#pushButton{border-image:url(:/icon/btn1.svg);}"
                        "#pushButton_2{border-image:url(:/icon/btn2.svg);}"
                        "#pushButton_3{border-image:url(:/icon/btn3.svg);}"
                        "#groupBox{border:none}"

       );
    font2_setup();
}

