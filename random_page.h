#ifndef RANDOM_PAGE_H
#define RANDOM_PAGE_H

#include <QObject>
#include <QWidget>
#include "ElaScrollPage.h"
#include "ElaFlowLayout.h"
#include "ElaImageCard.h"
#include "ElaMessageBar.h"
#include "ElaScrollArea.h"
#include "ElaText.h"
#include "ElaPushButton.h"
#include "ElaScrollPageArea.h"
#include "ElaContentDialog.h"
#include "QSettings"
#include <QRandomGenerator>
#include <QDebug>
#include <QVBoxLayout>
#include <QProcess>
#include <QCoreApplication>
#include <QTimer>
#include "ElaWindow.h"
#include "QTcpSocket"
#include "QHostInfo"
#include "QUrl"
#include "QDesktopServices"
class Random_page : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit Random_page(QWidget *parent = nullptr,ElaWindow *window = nullptr);
    ~Random_page();
    QWidget *ui;
    ElaText *Name;
    ElaText *tips;
    ElaPushButton *pushBtn_start;
    ElaPushButton *pushBtn_Five;
    ElaPushButton *pushBtn_clearLog;
    ElaText *log;
    int log_count;
    int AllowDuplicate_ini;
    QTcpSocket *tcpClient;
    QString version;
    QString version_pre;
    QTimer *timer;
    bool AutoUpdate(QString host_ip, QString remote_path, QString local_path, QString username, QString password);
    void do_AutoUpdate();

private slots:
    QString Random_Students(bool isclicked);
    void Random_Student_Five(bool isclicked);
    void do_timeout();
    void _closeEvent()
    {
        _window->closeWindow();
    }
    void on_pushBtn_clearLog(bool isclicked){
        log->clear();
        Name->setText(" ");
        log_count = 0;
    }
    void _update()
    {
        QUrl url("https://www.baidu.com/");
        QDesktopServices::openUrl(url);
    }
private:
    //QString *students;
    ElaWindow *_window;
    QString *students;
    int student_count = 0;

signals:
};

#endif // RANDOM_PAGE_H
