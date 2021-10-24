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
    authenticator = cv::face::MACE::create();
    initRecognizer();
}

void CvCam::setLabelBuffer(QString bufferText)
{
    labelBuffer = bufferText;
}

void CvCam::initRecognizer()
{
    std::vector<cv::Mat> imgList;
    std::vector<cv::Mat> authList;
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
        if(line->length() == 0)
            continue;
        QList<QByteArray> args = line->split(',');
        if(args.length() == 2)
        {
            QDir subDir = dir;
            int id = args[0].toInt();
            subDir.cd(args[0]);
            nameMap[id] = args[1];
            foreach(auto file, subDir.entryList(QDir::Files | QDir::NoDotAndDotDot))
            {
                qDebug() << id << args[1] << subDir.absoluteFilePath(file);
                cv::Mat mat = cv::imread(subDir.absoluteFilePath(file).toStdString(), 0);
                imgList.push_back(mat);
                idList.push_back(id);
                if(id == 0)
                    authList.push_back(mat);
            }
        }
    }
    recognizer->train(imgList, idList);
    authenticator->train(authList);
}

QRect CvCam::detectFace(cv::Mat img)
{
    std::vector<cv::Rect> faces;
    classifier->detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(img.cols * 0.3, img.rows * 0.3));
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
    bool authResult;
    recognizer->predict(img, label, confidence);
    authResult = authenticator->same(img);
    qDebug() << "predict:" << label << confidence;
    qDebug() << "auth:" << authResult;
    if(authResult)
    {
        emit verified();
        return nameMap[0];
    }
    else if(label > 0 && confidence > 30)
        return nameMap[label];
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
        cv::rectangle(*rawFrame, cv::Rect(faceArea.x(), faceArea.y(), faceArea.width(), faceArea.height()), cv::Scalar(255, 10, 10), 3);
        id = recognize(grey);
        qDebug() << "recognize:" << id;
        if(!id.isEmpty())
        {
            if(id == nameMap[0])
            {
                cv::rectangle(*rawFrame, cv::Rect(faceArea.x(), faceArea.y(), faceArea.width(), faceArea.height()), cv::Scalar(10, 255, 10), 3);
                cv::putText(*rawFrame, id.toStdString(), cv::Point(faceArea.x() + faceArea.width(), faceArea.y() + faceArea.height()), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(10, 255, 10));
            }
            else
            {
                cv::putText(*rawFrame, id.toStdString(), cv::Point(faceArea.x() + faceArea.width(), faceArea.y() + faceArea.height()), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 10, 10));
            }
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
    if(roiFrame->cols != 0 && roiFrame->rows != 0){
        emit frameAddr(rawFrame, roiFrame, roiOfRawFrame);
    }
    else{
        emit frameAddr(rawFrame, nullptr, nullptr);
    }
}
