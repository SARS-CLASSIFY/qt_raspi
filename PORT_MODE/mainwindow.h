#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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


#include <QSerialPort>
#include <camera.h>
#include <fix.h>
#include <music.h>

//weather
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


//sys time

#include <QTimer>
#include <qdatetime.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum Page
    {
        InitPage = 0,
        CameraPage,
        FixPage,
        MusicPage
    };

private slots:
    //personal
    void fullscreen();
    void window_init();
    void keyPressEvent(QKeyEvent *event);
    void font_setup(void);
    void qmovie_setup(void);

    //页面切换
    void change_to_camera();
    void change_to_fix();
    void change_to_music();
    void init_window();
    //时间日期及温度设定接口函数
    void time_set(QString current_time);
    void date_set(QString current_date);
    void temperature_set(QString current_temp);
    //指令控制相关函数
//    void on_nextButton_clicked();

//    void on_backButton_clicked();

//    void on_upButton_clicked();

//    void on_downButton_clicked();
//    void on_pushButton_6_clicked();
    //天气
    void checkW();
    void replyFinished(QNetworkReply *reply);
    //时间
    void timerUpdate(void);



    void onSerialReadyRead();

    void main_page_set(Page page);


    //DHT11
    void DHT11_Data_Handle(QByteArray myhmi);

    void unlock();
private:
    Ui::MainWindow *ui;
    //personal
    QString dir = QCoreApplication::applicationDirPath();
    QStringList m_fontList;
    QFont font;
    /*----qmovie-------*/
    QMovie *showGif, *showGif1;
    QImage *whether_img;
    /*----页面切换------*/
    fix *win3 = new fix;
    camera *win2 = new camera;
    music *win4 = new music;
    //天气
    QNetworkAccessManager *manager;  //请求句柄
    QString fengli;       //风力
    QString wendu;        //温度
    QString weather_type;  //天气类型

    QByteArray serialBuf;
    QSerialPort port;

    Page currentPage = InitPage;
    bool locked = true;

    //界面绝对坐标

    void changePage(int direction);
};

#endif // MAINWINDOW_H
