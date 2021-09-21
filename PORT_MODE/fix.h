#ifndef FIX_H
#define FIX_H

#include <QWidget>
#include <qlabel.h>


namespace Ui {
class fix;
}

class fix : public QWidget
{
    Q_OBJECT

public:
    explicit fix(QWidget *parent = 0);
    ~fix();

private slots:
    void change_to_back();
    void keyPressEvent(QKeyEvent *event);
    //personal

    void window3_init();
    void font3_setup(void);
    void pic_set(QLabel *label,QString fileaddress);
    void pic_change(int up_or_down);


private:
    Ui::fix *ui;

    //图片路径
    QString addre1 = ":/resourses/1.jpeg";
    QString addre2 = ":/resourses/2.jpeg";
    QString addre3 = ":/resourses/3.jpeg";
    QString addre4 = ":/resourses/4.jpeg";
    QString addre5 = ":/resourses/5.jpg";

};

#endif // FIX_H
