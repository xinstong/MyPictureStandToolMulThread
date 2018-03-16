#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myworkthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_scan_clicked();

    void on_pushButton_start_convert_clicked();

    void on_lineEdit_path_textChanged(const QString &arg1);

    void handleReportDegree(int value);

    void handleThreadDone();
private:
    Ui::MainWindow *ui;

    myWorkThread*   m_myThread;
};

#endif // MAINWINDOW_H
