#include "cvcam.h"

CvCam::CvCam(QThread* thread, QObject *parent) : QObject(parent)
{
    this->thread = thread;
    moveToThread(thread);
    cam = new cv::VideoCapture;
    rawFrame = new cv::Mat;
    roiFrame = new cv::Mat;
    roiOfRawFrame = new cv::Mat;
    refreshTimer = new QTimer;
    ocrTimer = new QElapsedTimer;
    refreshTimer->moveToThread(thread);
    refreshTimer->setInterval(50);
    connect(refreshTimer, &QTimer::timeout, this, &CvCam::onRefreshTimeout);
}

void CvCam::setLabelBuffer(QString bufferText)
{
    labelBuffer = bufferText;
}

void CvCam::openCam(int id)
{
    bool res = cam->open(id);
    qDebug() << res;
    if(res)
    {
        refreshTimer->start();
    }
    getRectResult();
    emit frameAddr(rawFrame, roiFrame, roiOfRawFrame);
}

void CvCam::onRefreshTimeout()
{
    bool readResult = cam->read(*rawFrame);
    if(!readResult)
    {
        cam->release();
        for(int i = 0; i < 10; i++)
        {
            if(cam->open(i))
                break;
        }
    }
    getRectResult();
    emit frameRefreshed();
}

void CvCam::closeCam()
{
    refreshTimer->stop();
    cam->release();
}

void CvCam::getFrameAddr()
{
    if(roiFrame->cols != 0 && roiFrame->rows != 0)
        emit frameAddr(rawFrame, roiFrame, roiOfRawFrame);
    else
        emit frameAddr(rawFrame, nullptr, nullptr);
}