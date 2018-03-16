#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QCoreApplication>
#include "myworkthread.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_myThread(NULL)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    qDebug() << "main window destrorying...";
    if (m_myThread)
    {
        m_myThread->quit();
    }

    delete ui;
}

void MainWindow::on_pushButton_scan_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "please the folder to convert", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (path != "")
    {
        ui->lineEdit_path->setText(path);
    }
}

void MainWindow::on_pushButton_start_convert_clicked()
{
    qDebug() << "thread started.";
    QString targetPath = ui->lineEdit_path->text();
    if (!m_myThread)
    {
        m_myThread = new myWorkThread(targetPath);
    }

    connect(m_myThread, SIGNAL(reportDegree(int)), this, SLOT(handleReportDegree(int)), Qt::QueuedConnection);
    connect(m_myThread, SIGNAL(finished()), this, SLOT(handleThreadDone()));
    m_myThread->start();

    qDebug() << "thread working " << " at thread: " << QThread::currentThreadId();
    ui->pushButton_start_convert->setEnabled(false);
}

void MainWindow::on_lineEdit_path_textChanged(const QString &arg1)
{
    qDebug() << "new path:" << arg1;

    if(QDir(arg1).exists())
    {
        ui->pushButton_start_convert->setEnabled(true);
    }
    else
    {
        ui->pushButton_start_convert->setEnabled(false);
    }
}

void MainWindow::handleReportDegree(int value)
{
    qDebug() << "get degree " << value << " at thread: " << QThread::currentThreadId();
    ui->progressBar_convert->setValue(value);
    update();
}

void MainWindow::handleThreadDone()
{
    qDebug() << "destory the thread.";
    m_myThread->quit();
    delete(m_myThread);
    m_myThread = NULL;

    ui->pushButton_start_convert->setEnabled(true);
}
