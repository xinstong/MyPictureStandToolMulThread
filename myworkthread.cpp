#include "myworkthread.h"
#include <QEventLoop>
#include <QCoreApplication>
#include <QProgressBar>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QImage>

myWorkThread::myWorkThread(QString& path)
    : m_path(path)
{

}


myWorkThread::~myWorkThread()
{

}


void myWorkThread::run()
{
    qDebug() << "thread run in." << " at thread: " << QThread::currentThreadId();

    QDir targetDir(m_path);
    if (!targetDir.exists())
    {
        qDebug() << "ERR: in thread, path dir not exist.";
        qDebug() << "thread run out.";
        return;
    }

    QStringList nameFilters;
    nameFilters << QString("*.jpeg")
            << QString("*.jpg")
            << QString("*.png")
            << QString("*.bmp");

    int iAllFileNum = 0;
    QDirIterator dirIteratorCount(m_path, nameFilters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(dirIteratorCount.hasNext())
    {
        dirIteratorCount.next();
        iAllFileNum++;
    }
    if (0 == iAllFileNum)
    {
        qWarning() << "WAN: in thread, the number of need conver file is zero.";
        qWarning() << "thread run out.";
        return;
    }


    QDirIterator dirIteratorConv(m_path, nameFilters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    QImage qImage;
    QString abFilePath("");
    int iDoneNum = 0;
    emit reportDegree(0);
    while(dirIteratorConv.hasNext())
    {
        do
        {
            dirIteratorConv.next();
            abFilePath = dirIteratorConv.fileInfo().absoluteFilePath();
            if (!qImage.load(abFilePath))
            {
                qDebug() << "ERR: QImage load file failed[" << abFilePath << "].";
                break;
            }

            if (!qImage.save(abFilePath))
            {
                qDebug() << "ERR: QImage conv file failed[" << abFilePath << "].";
            }
            else
            {
                qInfo() << "SESS: conv ok[" << abFilePath << "]";
            }
        }while(0);
        msleep(10);
        iDoneNum++;

        emit reportDegree((int)((iDoneNum * 100.0f) / (iAllFileNum * 1.0f)));
    }

    emit reportDegree(100);

    qDebug() << "thread run out.";
}
