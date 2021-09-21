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



#include <camera.h>
#include <fix.h>

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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    void init_window();
    //时间日期及温度设定接口函数
    void time_set(QString current_time);
    void date_set(QString current_date);
    void temperature_set(QString current_temp);
    //指令控制相关函数
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    //天气
    void checkW();
    void replyFinished(QNetworkReply *reply);
    //时间
    void timerUpdate(void);

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    //personal
    QString dir = QCoreApplication::applicationDirPath();
    QStringList m_fontList;
    QFont font;
    /*----qmovie-------*/
    QMovie *showGif;
    QImage *whether_img;
    /*----页面切换------*/
    fix *win3 = new fix;
    camera *win2 = new camera;
    //天气
    QNetworkAccessManager *manager;  //请求句柄
    QString fengli;       //风力
    QString wendu;        //温度
    QString weather_type;  //天气类型

};

#endif // MAINWINDOW_H
