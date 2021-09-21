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

    //时间日期及温度设定接口函数
    void time_set(QString current_time);
    void date_set(QString current_date);
    void temperature_set(QString current_temp);

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


};

#endif // MAINWINDOW_H
