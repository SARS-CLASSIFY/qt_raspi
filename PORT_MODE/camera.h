#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include "cvcam.h"

//page
namespace Ui
{
class camera;
}

class camera : public QWidget
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = nullptr);
    ~camera();
    CvCam* getCvCam()
    {
        return cvCam;
    }

    void setState(bool state);
private slots:
    void keyPressEvent(QKeyEvent *event);

    void change_to_next();
    void change_to_back();
    void window2_init();
    void font2_setup(void);

    void onVerified();
private:
    Ui::camera *ui;
    CvCam* cvCam;
    QThread* cvThread;
    cv::Mat* rawFrame;

    QPixmap mat2Pixmap(cv::Mat *mat);
public slots:
    void onFrameRefreshed();
    void onFrameAddrFetched(cv::Mat *rawAddr, cv::Mat *roiAddr, cv::Mat *roiOfRawAddr);

signals:
    void openCam(int id);
    void getFrameAddr();
    void closeCam();
    void unlocked();
};

#endif // CAMERA_H
