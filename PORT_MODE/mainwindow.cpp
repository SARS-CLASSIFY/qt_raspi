#include "mainwindow.h"
#include "ui_mainwindow.h"


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

//personal
#include <QKeyEvent>
#include <camera.h>


/*---------------------------------gui界面测试部分-----------------------
 * 使用按钮进行界面切换调试，可以换成通过串口信息进行页面切换
 * 布局可以根据后续需要进一步修改
 * 需要添加功能可以先创建基本控件，后续优化
 * --------------------------------------------------------------------*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //界面初始化
    window_init();
//    fullscreen();//全屏显示

}

MainWindow::~MainWindow()
{
    delete ui;
}


//personal
/*---------------------------------------------------------
 * 全屏设置函数
 * -------------------------------------------------------*/
void MainWindow::fullscreen()
{
    QWidget::showFullScreen();
}


/*------------------------------------------------------------
 * 界面样式设置函数
 * ------------------------------------------------------------*/
void MainWindow::window_init()
{

    //背景设置
//    this->setStyleSheet("#centralWidget{border-image:url(:/timg.jpg);}" //设置指定图片为背景
    this->setStyleSheet("#centralWidget{background:rgba(0,0,0,1);}" //设置主界面背景透明度
        "#label{background:rgba(255,255,0,1.0);}"
        "#page1{background:rgba(0,0,0,1.0);}"
        "#whether{border-image:url(:/icon/cloud.png);}"
        "#pushButton_3{border-image:url(:/icon/btn3.svg);}"
        "#groupBox_3{border:none}"     //用于消除边框
        "#groupBox_2{border:none}"
       );
    //字体设置
    font_setup();
    //动图设置
    qmovie_setup();
}

/*-------------------------------------------------------
 * 按键响应函数（测试使用）
 * ------------------------------------------------------*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    //判断ESC按键事件
    case Qt::Key_Escape:
        QWidget::showNormal();
        break;
    //del键用于退出 全屏调试使用
    case Qt::Key_Delete:
        QApplication* app;
        app->quit();
        break;
    case Qt::Key_Right:
        change_to_camera();
        break;
    default:
        break;
    }
}


/*------------------------------------------------------
 * 字体样式设置
 * ------------------------------------------------------*/
void MainWindow::font_setup(void)
{

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
        font.setPixelSize(30);//设置字体大小
        font.setBold(true);//斜体
    }

    //标签测试
    ui->main_theam->setFont(font);//主题
    ui->main_theam->setStyleSheet("background-color: rgb(0, 0, 0);font-size:30px;color:white");
    ui->main_theam->setText("MAGIC MIRROR");

    //日期设置
    date_set("9月14日");

    //时间设置
//    int t1 =8,t2=22;
//    QString current_time;
//    current_time+=QString::number(t1)+":"+QString::number(t2);
    time_set("8:23");

    //温度设置
//    int tp = 23;
//    QString current_temp;
//    current_temp+=QString::number(tp)+"℃";
     temperature_set("20℃");

}


/*---------------------------------------------------------------------------
 * gif动图设置
-----------------------------------------------------------------------------------*/
void MainWindow::qmovie_setup(void)
{
    showGif = new QMovie(":/gif1.gif");
    //设置适应Qlabel大小
    QSize my_size = ui->labelGif->size();
    showGif->setScaledSize(my_size);

    ui->labelGif->setMovie(showGif);
    showGif->start();

}



/*---------------------------------------------------
 * 页面切换(转到下一页面)
 * ------------------------------------------------*/
void MainWindow::change_to_camera()
{
    camera *win2;
    win2 = new camera;
    this->hide();
    win2->show();

}

/*--------------------------------------------------
 * 时间设定函数接口
 * -------------------------------------------------*/
void MainWindow::time_set(QString current_time)
{
    //非qstring型可以如下转换
//    int t1 =8,t2=22;
//    QString current_time;
//    current_time+=QString::number(t1)+":"+QString::number(t2);
    ui->c_time->setFont(font);
    ui->c_time->setStyleSheet("background-color: rgb(0, 0, 0);font-size:40px;color:rgb(192,192,192)");
    ui->c_time->setText(current_time);

}

/*--------------------------------------------
 * 日期设定函数接口
 * ------------------------------------------------*/
void MainWindow::date_set(QString current_date)
{
    ui->date->setFont(font);//日期
    ui->date->setStyleSheet("background-color: rgb(0, 0, 0);font-size:20px;color:white");
//    ui->date->setText("星期日\n8月23日");
    ui->date->setText(current_date);
}

/*-------------------------------------------------
 * 温度设定函数接口
 * ------------------------------------------------*/
void MainWindow::temperature_set(QString current_temp)
{
    //非qstring型可以如下转换
//    int tp = 23;
//    current_temp+=QString::number(tp)+"℃";
    ui->temperature->setFont(font);
    ui->temperature->setStyleSheet("background-color: rgb(0, 0, 0);font-size:25px;color:rgb(192,192,192)");
    ui->temperature->setText(current_temp);
}


