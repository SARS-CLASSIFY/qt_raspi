#ifndef CVCAM_H
#define CVCAM_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QRect>
#include <QFile>
#include <QImage>
#include <QProcess>
#include <QElapsedTimer>
#include <opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/face/facerec.hpp>
#include <opencv2/face/mace.hpp>
#include <opencv2/core.hpp>

class CvCam : public QObject
{
    Q_OBJECT
public:
    explicit CvCam(QThread* thread, QObject *parent = nullptr);

public slots:
    void openCam(int id);
    void getFrameAddr();
    void closeCam();
    void setLabelBuffer(QString bufferText);
signals:
    void OCRResult(QString result);
    void frameRefreshed();
    void frameAddr(cv::Mat* rawAddr, cv::Mat* roiAddr, cv::Mat* roiOfRawAddr);
    void drugRect(QRect rect);
    void verified();
private slots:
    void onRefreshTimeout();
private:
    QThread* thread;
    cv::VideoCapture* cam;
    QTimer* refreshTimer;
    cv::Mat* rawFrame;
    cv::Mat* roiFrame;
    cv::Mat* roiOfRawFrame;
    cv::CascadeClassifier* classifier;
    cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer;
    cv::Ptr<cv::face::MACE> authenticator;
    QMap<int, QString> nameMap;
    QElapsedTimer* ocrTimer;
    QString labelBuffer;
    QRect detectFace(cv::Mat img);
    void initRecognizer();
    QString recognize(cv::Mat img);
};

#endif // CVCAM_H
