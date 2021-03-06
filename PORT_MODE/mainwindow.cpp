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
#include <fix.h>
#include <music.h>

//Debug output
#include <QDebug>


#include <QMediaPlayer>
#include <QMediaPlaylist>

/*---------------------------------gui界面测试部分-----------------------
 * 使用按钮进行界面切换调试，可以换成通过串口信息进行页面切换
 * 布局可以根据后续需要进一步修改
 * 需要添加功能可以先创建基本控件，后续优化
 * --------------------------------------------------------------------*/
//主窗口坐标

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //界面初始化
    window_init();
    //fullscreen();//全屏显示
    //去掉窗口变框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setGeometry(0, 0, 1024, 600);

    //天气
    manager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));//关联信号和槽
    checkW();
//    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(checkW()));//关联信号和槽

    //系统时间
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(1000);
    port.setBaudRate(115200);
    port.setPortName("/dev/ttyACM0");
//    port.setPortName("COM1");
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setFlowControl(QSerialPort::SoftwareControl);
    port.setStopBits(QSerialPort::OneStop);
    connect(&port, &QSerialPort::readyRead, this, &MainWindow::onSerialReadyRead);
    qDebug() << "open serialport:" << port.open(QIODevice::ReadWrite);
    connect(win2, &camera::unlocked, this, &MainWindow::unlock);

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
                        "#groupBox_3{border:none}"     //用于消除边框
                        "#groupBox_2{border:none}"
                        "#pagex{background:rgba(255,255,0,1.0);}"
                        "#groupBox{border:none}"
                       );
    //字体设置
    font_setup();
    //hide
    ui->labelGIF3->hide();
    ui->my_txt1->hide();
    ui->my_txt2->hide();
    //动图设置
    qmovie_setup();

}

/*-------------------------------------------------------
 * 按键响应函数（测试使用）
 * ------------------------------------------------------*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    //判断ESC按键事件
    case Qt::Key_Escape:
        QWidget::showNormal();
        break;
    //del键用于退出 全屏调试使用
    case Qt::Key_Delete:
        QApplication::quit();
        break;
    case Qt::Key_A:
        change_to_camera();
        break;
    case Qt::Key_B:
        change_to_fix();
        break;
    case Qt::Key_Left:
        changePage(-1);
        break;
    case Qt::Key_Right:
        changePage(1);
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
    if(lcdFontId != -1)  // -1为加载失败
    {
        m_fontList << QFontDatabase::applicationFontFamilies(lcdFontId);
    }
    if(!m_fontList.isEmpty())
    {

        font.setFamily(m_fontList.at(0));//设置字体样式
        font.setPixelSize(30);//设置字体大小
        font.setBold(true);//斜体
    }

    //标签测试
    ui->main_theam->setFont(font);//主题
    ui->main_theam->setStyleSheet("background-color: rgb(0, 0, 0);font-size:50px;color:white");
//    ui->main_theam->setText("MAGIC MIRROR");

    //日期设置
    date_set("9月14日");

    //时间设置
    time_set("8:23");

    //温度及天气设置
    temperature_set("20℃");
    ui->type->setStyleSheet("background-color: rgb(0, 0, 0);font-size:20px;color:rgb(192,192,192)");
    ui->fengli->setStyleSheet("background-color: rgb(0, 0, 0);font-size:20px;color:rgb(192,192,192)");
    ui->labelX->setStyleSheet("background-color: rgb(0, 0, 0);font-size:20px;color:rgb(192,192,192)");

    //穿搭标签字体
    ui->my_txt1->setStyleSheet("background-color: rgb(0, 0, 0);font-size:40px;color:rgb(192,192,192)");
    ui->my_txt2->setStyleSheet("background-color: rgb(0, 0, 0);font-size:18px;color:rgb(192,192,192)");
}


/*---------------------------------------------------------------------------
 * gif动图设置
-----------------------------------------------------------------------------------*/
void MainWindow::qmovie_setup(void)
{
    showGif = new QMovie(":/gif1.gif");
    showGif1 = new QMovie(":/gif2.gif");
    //设置适应Qlabel大小
    QSize my_size = ui->labelGif->size();
    showGif->setScaledSize(my_size);

    QSize my_size2 = ui->labelGif2->size();
    showGif1->setScaledSize(my_size2);

    ui->labelGif->setMovie(showGif);
    showGif->start();

    ui->labelGif2->setMovie(showGif1);
    showGif1->start();

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
    //ui->c_time->setFont(font);
    ui->c_time->setStyleSheet("background-color: rgb(0, 0, 0);font-size:20px;color:rgb(192,192,192)");
    ui->c_time->setText(current_time);

}

/*--------------------------------------------
 * 日期设定函数接口
 * ------------------------------------------------*/
void MainWindow::date_set(QString current_date)
{
//    //ui->date->setFont(font);//日期
//    ui->date->setStyleSheet("background-color: rgb(0, 0, 0);font-size:20px;color:white");
//    ui->date->setText("星期日\n8月23日");
//    ui->date->setText(current_date);
}

/*-------------------------------------------------
 * 温度设定函数接口
 * ------------------------------------------------*/
void MainWindow::temperature_set(QString current_temp)
{
    //非qstring型可以如下转换
//    int tp = 23;
//    current_temp+=QString::number(tp)+"℃";
    //ui->temperature->setFont(font);
    ui->temperature->setStyleSheet("background-color: rgb(0, 0, 0);font-size:25px;color:rgb(192,192,192)");
    ui->temperature->setText(current_temp);
}




//PAGE

/*--------------------------------------------
 * 切换到下一界面
 * ---------------------------------------------*/
void MainWindow::change_to_fix()
{
    //fix *win3 = new fix;
    //this->hide();
    ui->page1->hide();
    win2->hide();
    win4->hide();


    ui->labelGIF3->hide();
    ui->my_txt1->hide();
    ui->my_txt2->hide();

    win3->show();


}


/*---------------------------------------------------
 *以下是页面切换及功能指令（用串口替换）
 * ------------------------------------------------*/
void MainWindow::change_to_camera()
{
//    camera *win2;
//    win2 = new camera;
    //this->hide();
    ui->page1->hide();
    ui->labelGIF3->hide();
    ui->my_txt1->hide();
    ui->my_txt2->hide();


    win3->hide();
    win4->hide();
    win2->show();

}


void MainWindow::change_to_music()
{
    ui->page1->hide();
    win3->hide();
    win2->hide();

    ui->labelGIF3->hide();
    ui->my_txt1->hide();
    ui->my_txt2->hide();

    win4->show();

}

/*--------------------------------------------------
 * 切换到初始界面
 * --------------------------------------------------*/
void MainWindow:: init_window()
{
    win3->hide();
    win2->hide();
    win4->hide();
    //ui->widget->show();
    cloth_recommend(wendu);
    ui->page1->show();

}


//void MainWindow::on_nextButton_clicked()
//{
//    change_to_camera();
//}

//void MainWindow::on_backButton_clicked()
//{
//    change_to_fix();
//}

//void MainWindow::on_pushButton_6_clicked()
//{
//    init_window();
//}

//void MainWindow::on_upButton_clicked()
//{
//    win3->pic_change(1);
//}

//void MainWindow::on_downButton_clicked()
//{
//    win3->pic_change(0);
//}


/*-----------------------------------------------------------------------------------
 * 天气及时间显示部分
 * ------------------------------------------------------------------------------*/
void MainWindow::checkW() //点击查询请求天气数据
{
    QString local_city = "杭州" ;//获得需要查询天气的城市名称
    char quest_array[256] = "http://wthrcdn.etouch.cn/weather_mini?city=";
    QNetworkRequest quest;
    sprintf(quest_array, "%s%s", quest_array, local_city.toUtf8().data());
    quest.setUrl(QUrl(quest_array));
    quest.setHeader(QNetworkRequest::UserAgentHeader, "RT-Thread ART");
    /*发送get网络请求*/
    manager->get(quest);
}

void MainWindow::replyFinished(QNetworkReply *reply)  //天气数据处理槽函数
{
    qDebug() << "recv weather data!!";
    QString all = reply->readAll();

    //ui->textBrowser->setText(all); //将接收到的数据显示出来

    QJsonParseError err;
    QJsonDocument json_recv = QJsonDocument::fromJson(all.toUtf8(), &err);//解析json对象
    qDebug() << err.error;
    if(!json_recv.isNull())
    {
        QJsonObject object = json_recv.object();

        if(object.contains("data"))
        {
            QJsonValue value = object.value("data");  // 获取指定 key 对应的 value
            if(value.isObject())
            {
                QJsonObject object_data = value.toObject();
                if(object_data.contains("forecast"))
                {
                    QJsonValue value = object_data.value("forecast");
                    if(value.isArray())
                    {
                        QJsonObject today_weather = value.toArray().at(0).toObject();
                        weather_type = today_weather.value("type").toString();

                        QString tuijian = object.value("data").toObject().value("ganmao").toString();
                        QString low = today_weather.value("low").toString();
                        QString high = today_weather.value("high").toString();
                        wendu = low.mid(low.length() - 3, 4) + "~" + high.mid(high.length() - 3, 4);
                        QString strength = today_weather.value("fengli").toString();
                        strength.remove(0, 8);
                        strength.remove(strength.length() - 2, 2);
                        fengli = today_weather.value("fengxiang").toString() + strength;

                        ui->type->setText(weather_type); //显示天气类型
                        ui->temperature->setText(wendu);   //显示温度
                        ui->fengli->setText(fengli); //显示风力
                    }
                }
            }
        }

    }
    else
    {
        qDebug() << "json_recv is NULL or is not a object !!";
    }
    reply->deleteLater(); //销毁请求对象
}

//获取当前时间

void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy\nMM-dd\nhh:mm:ss\ndddd");
    ui->c_time->setText(str);
}

void MainWindow::onSerialReadyRead()
{
    serialBuf += port.readAll();
    qDebug() << serialBuf;
    if(serialBuf.endsWith('>'))
    {
        //湿度数据显示
        if(serialBuf[0] == 't')
        {
            DHT11_Data_Handle(serialBuf);
        }


        if(serialBuf == "1>")
        {
            changePage(-1);
        }
        else if(serialBuf == "2>")
        {
            changePage(1);
        }
        else if(serialBuf == "4>")
            win3->pic_change(1);
        else if(serialBuf == "8>")
            win3->pic_change(0);

        else if(serialBuf == "get>")//获取天气信息
            checkW();

        //音乐播放部分
        else if(serialBuf == "start>")
            win4->play_status();
        else if(serialBuf == "stop>")
            win4->play_status();
        else if(serialBuf == "next>")
            win4->on_nextSong_clicked();
        else if(serialBuf == "back>")
            win4->on_firstSong_clicked();

        else if(serialBuf == "key>" || serialBuf == "lock>")
        {
            locked = true;
            main_page_set(InitPage);
        }

        serialBuf.clear();
    }
}


//yemianqiehan
void MainWindow::main_page_set(Page page)
{
    currentPage = page;
    if(page == CameraPage)
    {
        win2->setState(true);
        port.write("c1>", 3);
    }
    else
    {
        win2->setState(false);
        port.write("c0>", 3);
    }
    switch(page)
    {
    case InitPage:
        init_window();
        break;
    case CameraPage:
        change_to_camera();
        break;
    case FixPage:
        change_to_fix();
        break;
    case MusicPage:
        change_to_music();
        break;
    default:
        break;

    }

}


/*--------------------DHT11设置函数-------------------
 * myhmi:传入串口数据
 * ----------------------------------------------------*/
void MainWindow::DHT11_Data_Handle(QByteArray myhmi)
{
    QString StrI1 = tr(myhmi.mid(myhmi.lastIndexOf(",") + 1, 4)); //自定义了简单协议，通过前面字母读取需要的数据
    if(sizeof(StrI1) > 0)
    {
        ui->labelX->setText(StrI1 + "%RH");
    }
}

void MainWindow::changePage(int direction)
{
    Page newPage = (Page)((currentPage + direction + 4) % 4);
    qDebug() << "newPage:" << newPage << locked;
    if(!locked)
    {
        main_page_set(newPage);
    }
    else if(locked && (newPage == InitPage || newPage == CameraPage))
    {
        main_page_set(newPage);
    }
}

void MainWindow::unlock()
{
    if(locked)
        port.write("f\x05\x40\x05>", 5);
    locked = false;
}



//穿搭推荐部分
/*------------------------------------------------
 * 图片设置功能
 * ---------------------------------------------*/

void MainWindow::cloth_change(QLabel *label, QString fileaddress)
{
    QImage *img = new QImage; //新建一个image对象



    img->load(fileaddress); //将图像资源载入对象img，注意路径，可点进图片右键复制路径

    img->scaled(label->size(), Qt::KeepAspectRatio);
    label->setScaledContents(true);
    label->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
}

/*----------------------------------------------
 * 穿搭切换逻辑
 * --------------------------------------------*/
void MainWindow::cloth_recommend(QString wendu)
{
    QString s;
    s = wendu.mid(0, wendu.indexOf("~") - 1);
    int get_temp = s.toInt();
    qDebug() << get_temp;

    if(get_temp <= 20 && get_temp >= 10)
    {
        cloth_change(ui->labelGIF3, addrea);
        ui->my_txt2->setText("推荐穿搭:\n夹克\n天气转冷\n小心着凉");
    }
    else if(get_temp <= 10 && get_temp >= 0)
    {
        cloth_change(ui->labelGIF3, addrec);
        ui->my_txt2->setText("推荐穿搭:\n夹克\n天气转冷\n小心着凉");
    }
    else if(get_temp < 0)
    {
        cloth_change(ui->labelGIF3, addree);
        ui->my_txt2->setText("推荐穿搭:\n棉衣棉裤\n天气转冷\n小心着凉");
    }
    else if(get_temp > 20)
    {
        cloth_change(ui->labelGIF3, addred);
        ui->my_txt2->setText("推荐穿搭:\n短袖T恤\n天气较热\n清爽着装");
    }



    ui->labelGif->hide();
    if(locked == false){
        ui->labelGIF3->show();
        ui->my_txt1->show();
        ui->my_txt2->show();
    }
    else{
        ui->labelGif->show();
    }
}


