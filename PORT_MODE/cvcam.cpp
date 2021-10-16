#include "cvcam.h"
#include <QDir>
#include <QApplication>
#include <vector>

CvCam::CvCam(QThread* thread, QObject *parent) : QObject(parent)
{
    this->thread = thread;
    // moveToThread(thread);
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
    classifier = new cv::CascadeClassifier((dir.path() + "/faceClassify.xml").toStdString());
    recognizer = cv::face::LBPHFaceRecognizer::create();
    initRecognizer();
}

void CvCam::setLabelBuffer(QString bufferText)
{
    labelBuffer = bufferText;
}

void CvCam::initRecognizer()
{
    std::vector<cv::Mat> imgList;
    std::vector<int> idList;
    QDir dir(QApplication::applicationDirPath());
    dir.cd("data");
    qDebug() << dir.absoluteFilePath("info.csv");
    QFile info(dir.absoluteFilePath("info.csv"));
    info.open(QFile::ReadOnly | QFile::Text);
    QList<QByteArray> infoLines = info.readAll().split('\n');
    info.close();
    for(auto line = infoLines.begin(); line != infoLines.end(); line++)
    {
        QList<QByteArray> args = line->split(',');
        if(args.length() == 3)
        {
            imgList.push_back(cv::imread(dir.absoluteFilePath(args[0]).toStdString(), 0));
            idList.push_back(args[1].toInt());
            nameList.append(args[2]);
        }
    }
    recognizer->train(imgList, idList);
}

QRect CvCam::detectFace(cv::Mat img)
{
    std::vector<cv::Rect> faces;
    classifier->detectMultiScale(img, faces);
    if(faces.size() != 0)
    {
        return QRect(faces[0].x, faces[0].y, faces[0].width, faces[0].height);
    }
    else
    {
        return QRect();
    }
}

QString CvCam::recognize(cv::Mat img)
{
    int label = -1;
    double confidence = 0.0;
    recognizer->predict(img, label, confidence);
    qDebug() << "predict:" << label << confidence;
    if(label == 0)
        emit verified();
    if(label != -1 && confidence > 0.5)
        return nameList[label];
    else
        return QString();
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
    QRect faceArea;
    QString id;
    cv::Mat camFrame;
    bool readResult = cam->read(camFrame);
    cv::resize(camFrame, *rawFrame, cv::Size(0, 0), 0.5, 0.5);
    cv::Mat grey;
    cv::cvtColor(*rawFrame, grey, CV_BGR2GRAY);
    faceArea = detectFace(grey);
    if(faceArea.width() > 0 && faceArea.height() > 0)
    {
        cv::rectangle(*rawFrame, cv::Rect(faceArea.x(), faceArea.y(), faceArea.width(), faceArea.height()), cv::Scalar(255, 0, 0), 3);
        id = recognize(grey);
        if(!id.isEmpty())
        {
            cv::putText(*rawFrame, id.toStdString(), cv::Point(faceArea.x() + faceArea.width(), faceArea.y() + faceArea.height()), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 0, 0));
        }
    }

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
