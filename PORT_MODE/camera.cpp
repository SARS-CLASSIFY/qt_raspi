#include "camera.h"
#include "ui_camera.h"
#include <QDebug>
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
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->move(122, 162);//窗口移动

    cvThread = new QThread();
    cvCam = new CvCam(cvThread);
    cvThread->start();

    connect(this, &camera::openCam, cvCam, &CvCam::openCam);
    connect(this, &camera::closeCam, cvCam, &CvCam::closeCam);
    connect(this, &camera::getFrameAddr, cvCam, &CvCam::getFrameAddr);
    connect(cvCam, &CvCam::frameRefreshed, this, &camera::onFrameRefreshed);
    connect(cvCam, &CvCam::frameAddr, this, &camera::onFrameAddrFetched);

    emit openCam(0);

}

camera::~camera()
{
    delete ui;
}

QPixmap camera::mat2Pixmap(cv::Mat* mat)
{
    return QPixmap::fromImage(QImage((const unsigned char*)mat->data, mat->cols, mat->rows, mat->step, QImage::Format_RGB888).rgbSwapped());
}

void camera::onFrameRefreshed()
{
    if(rawFrame != nullptr)
    {
        ui->label->setPixmap(mat2Pixmap(rawFrame));
    }
}

void camera::onFrameAddrFetched(cv::Mat* rawAddr, cv::Mat* roiAddr, cv::Mat* roiOfRawAddr)
{
    qDebug()<<"frame addr:"<<rawAddr;
    this->rawFrame = rawAddr;
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
        font.setPixelSize(50);//设置字体大小
        font.setBold(true);//斜体
    }

    //标签测试
    ui->word->setFont(font);//主题
    ui->word->setStyleSheet("background-color: rgb(0, 0, 0);font-size:50px;color:white");
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

