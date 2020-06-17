#include "processcamera.h"
#include <QDebug>

ProcessCamera::ProcessCamera() : QThread()
{
    numb = 1;
    m_deviceID = 0;
    m_stopped = false;
    m_tracking = false;
    m_camera = new cv::VideoCapture();
    m_frameWidth = 640;
    m_frameHeight = 480;
}

ProcessCamera::~ProcessCamera()
{
}

void ProcessCamera::run()
{
    m_camera -> open(m_deviceID);
    m_camera -> set(CV_CAP_PROP_FRAME_WIDTH, m_frameWidth);
    m_camera -> set(CV_CAP_PROP_FRAME_HEIGHT, m_frameHeight);

    while (!m_stopped)
    {
        (*m_camera) >> m_frameOriginal;
        emit signalFrameToDetection(m_frameOriginal);

        if(!m_tracking)
        {
            process(m_frameOriginal);
        }
        else
        {
            emit signalFrameToTracking(m_frameOriginal);
        }

        msleep(20);
    }
}

void ProcessCamera::process(cv::Mat frame)
{
    if(numb == 1)
    {
        cv::cvtColor(frame, m_frameProcessed, cv::COLOR_BGR2RGB);
        outputFrame = QImage((const uchar *) m_frameProcessed.data, m_frameProcessed.cols, m_frameProcessed.rows, m_frameProcessed.step1(), QImage::Format_RGB888);
    }
    else if(numb == 2)
    {
        cv::cvtColor(frame, m_frameProcessed, cv::COLOR_BGR2GRAY);
        outputFrame = QImage((const unsigned char *) m_frameProcessed.data, m_frameProcessed.cols, m_frameProcessed.rows, m_frameProcessed.step1(), QImage::Format_Indexed8);
    }
    else if(numb == 3)
    {
        cv::Mat frameHSV;
        cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);
        cv::cvtColor(frameHSV, m_frameProcessed, cv::COLOR_BGR2RGB);
        outputFrame = QImage((const uchar *) m_frameProcessed.data, m_frameProcessed.cols, m_frameProcessed.rows, m_frameProcessed.step1(), QImage::Format_RGB888);

    }
    else if(numb == 4)
    {
        cv::Mat frameNegative;
        cv::bitwise_not(frame, frameNegative);
        cv::cvtColor(frameNegative, m_frameProcessed, cv::COLOR_BGR2RGB);
        outputFrame = QImage((const uchar *) m_frameProcessed.data, m_frameProcessed.cols, m_frameProcessed.rows, m_frameProcessed.step1(), QImage::Format_RGB888);
    }
    else if(numb == 5)
    {
        cv::Mat frameBlur;
        cv::blur( frame, frameBlur, cv::Size(3,3) );
        cv::Canny(frame, m_frameProcessed, 20, 200);
        outputFrame = QImage((uchar *) m_frameProcessed.data, m_frameProcessed.cols, m_frameProcessed.rows, m_frameProcessed.step1(), QImage::Format_Indexed8);
    };

    emit sendFrameProcessed(outputFrame);
}

void ProcessCamera::stop()
{
    m_stopped = true;
    delete m_camera;
}

void ProcessCamera::slotFrameTrackingToProcess(cv::Mat frame)
{
    process(frame);
}

void ProcessCamera::slotOnTrackingToProcess()
{
    m_tracking = true;
}

void ProcessCamera::slotOffTrackingToProcess()
{
    m_tracking = false;
}

void ProcessCamera::slotStartCamera()
{
    m_stopped = false;
}

void ProcessCamera::slotChangeCamera(int deviceID)
{
    m_stopped = true;
    m_deviceID = deviceID;
    msleep(100); //Wait camera off
}

void ProcessCamera::slotSetResolution(int resolution)
{
    switch (resolution)
    {
    case 1: { m_frameWidth = 1280; m_frameHeight = 720; break; }
    case 2: { m_frameWidth = 800; m_frameHeight = 600; break; }
    case 3: { m_frameWidth = 640; m_frameHeight = 480; break; }
    case 4: { m_frameWidth = 320; m_frameHeight = 240; break; }
    default: { m_frameWidth = 640; m_frameHeight = 480; }
    }
    m_stopped = true;
    msleep(150);
}

void ProcessCamera::setOriginal() { numb = 1; }
void ProcessCamera::setGrey() { numb = 2; }
void ProcessCamera::setHSV() { numb = 3; }
void ProcessCamera::setNegative() { numb = 4; }
void ProcessCamera::setCanny() { numb = 5; }
