#ifndef MYWORKTHREAD_H
#define MYWORKTHREAD_H

#include <QThread>

class QProgressBar;

class myWorkThread : public QThread
{
    Q_OBJECT

public:
    myWorkThread(QString& path);
    virtual ~myWorkThread();

public:
    // overwrite QThread
    virtual void run() Q_DECL_OVERRIDE;

signals:
    void reportDegree(int value);

private:
    QString         m_path;
};

#endif // MYWORKTHREAD_H
