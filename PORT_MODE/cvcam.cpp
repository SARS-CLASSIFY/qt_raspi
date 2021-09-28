#include "cvcam.h"
#include <QDir>
#include <QApplication>
#include <vector>

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
    refreshTimer->setInterval(150);
    connect(refreshTimer, &QTimer::timeout, this, &CvCam::onRefreshTimeout);
    QDir dir(QApplication::applicationDirPath());
    dir.cd("../PORT_MODE");
    classifier = new cv::CascadeClassifier((dir.path()+"/faceClassify.xml").toStdString());
}

void CvCam::setLabelBuffer(QString bufferText)
{
    labelBuffer = bufferText;
}

QRect CvCam::detectFace(cv::Mat img)
{
    cv::Mat grey;
    std::vector<cv::Rect> faces;
    cv::cvtColor(img, grey, CV_BGR2GRAY);
    classifier->detectMultiScale(grey, faces);
    if(faces.size() != 0)
    {
        cv::rectangle(*rawFrame, faces[0], cv::Scalar(255,0,0), 3);
        cv::putText(*rawFrame, "Owner",cv::Point(faces[0].x+faces[0].width, faces[0].y+faces[0].height),cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(255,0,0));
        return QRect(faces[0].x, faces[0].y, faces[0].width, faces[0].height);
    }
    return QRect();
}

void CvCam::openCam(int id)
{
    bool res = cam->open(id);
    qDebug() << "open camera result:" << res;
    if(res)
    {
        refreshTimer->start();
    }
    emit frameAddr(rawFrame, roiFrame, roiOfRawFrame);
}

void CvCam::onRefreshTimeout()
{
    cv::Mat camFrame;
    bool readResult = cam->read(camFrame);
    cv::resize(camFrame, *rawFrame, cv::Size(0,0), 0.5, 0.5);
    qDebug() << detectFace(*rawFrame);
    if(!readResult)
    {
        cam->release();
        for(int i = 0; i < 10; i++)
        {
            if(cam->open(i))
                break;
        }
    }
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
