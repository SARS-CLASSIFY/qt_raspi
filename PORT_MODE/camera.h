#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>

//page
namespace Ui {
class camera;
}

class camera : public QWidget
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = 0);
    ~camera();

private slots:
    void keyPressEvent(QKeyEvent *event);

    void change_to_next();
    void change_to_back();
    void window2_init();
    void font2_setup(void);

private:
    Ui::camera *ui;
};

#endif // CAMERA_H
