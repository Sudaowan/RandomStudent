#include "random_page.h"
#include <QFile>

Random_page::Random_page(QWidget *parent, ElaWindow *window)
    :   ElaScrollPage(parent)
{
    //students = new QString[55];

    _window = window;
    setPageTitleSpacing(5);
    // qDebug()<< QRandomGenerator::global()->bounded(0,10);

    ui = new QWidget(this);
    ui->setWindowTitle("◎抽签界面");

    //读取学生名单
    QString fileName = "Student.studentData";
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "success", "初始化名单成功!", 2000);
        QTextStream txtInput(&file);
        QByteArray str;
        student_count = 0;
        while(!txtInput.atEnd())
        {
            str = txtInput.readLine().toUtf8();
            student_count++;
            qDebug()<<student_count;
        }
        int i = 0;
        students = new QString[student_count];
        txtInput.seek(0);
        while(!txtInput.atEnd())
        {
            str = txtInput.readLine().toUtf8();
            qDebug() << (QString)QByteArray::fromBase64(str) << Qt::endl;
            students[i] = (QString)QByteArray::fromBase64(str);
            i++;
        }
    }
    else
    {
        // 如果文件打开失败，则输出错误信息
        qDebug() << "打开文件失败!";
        ElaMessageBar::error(ElaMessageBarType::BottomRight, "failure", "初始化名单失败!", 2000);
    }

    //读ini文件
    QSettings *m_IniFile = new QSettings("randomStudent.ini", QSettings::IniFormat);
    AllowDuplicate_ini = m_IniFile->value("RANDOM/AllowDuplicate").toInt();
    version = m_IniFile->value("VERSION/application").toString();
    delete m_IniFile;
    log_count = 0;

    pushBtn_start = new ElaPushButton();
    pushBtn_start->setText("随机一次");
    pushBtn_start->setMinimumSize(200,50);
    pushBtn_Five = new ElaPushButton();
    pushBtn_Five->setText("随机五次");
    pushBtn_Five->setMinimumSize(200,50);
    pushBtn_clearLog = new ElaPushButton();
    pushBtn_clearLog->setMinimumSize(100,50);
    pushBtn_clearLog->setText("清空");


    Name = new ElaText();
    QFont font = Name->font();
    font.setPointSize(50);
    Name->setFont(font);
    Name->setText(" ");
    tips = new ElaText();
    QFont font2 = tips->font();
    font2.setPointSize(11);
    tips->setFont(font2);
    tips->setText("<font color=\"#808080\">version-"+version+"-Release,正式版/更新时间-2024.06.22<\font>");
    log = new ElaText();
    log->setTextSize(21);

    QVBoxLayout *layout = new QVBoxLayout(ui);
    layout->setContentsMargins(10, 10, 0, 0);
    layout->addWidget(Name);
    QHBoxLayout *layout_btn = new QHBoxLayout(ui);
    layout_btn->addWidget(pushBtn_start);
    layout_btn->addWidget(pushBtn_Five);
    layout_btn->addWidget(pushBtn_clearLog);
    layout_btn->addStretch();
    layout->addLayout(layout_btn);
    layout->addWidget(log);
    layout->addStretch();
    layout->addWidget(tips);

    layout->setSpacing(20);//组件距离
    ui->setLayout(layout);
    addCentralWidget(ui);


    connect(pushBtn_start,SIGNAL(clicked(bool)),this,SLOT(Random_Students(bool)));
    connect(pushBtn_Five,SIGNAL(clicked(bool)),this,SLOT(Random_Student_Five(bool)));
    connect(pushBtn_clearLog,SIGNAL(clicked(bool)),this,SLOT(on_pushBtn_clearLog(bool)));

    //自动更新程序
    AutoUpdate("","","","","");//原来是有参数的，懒得改了
}

Random_page::~Random_page(){
}

QString Random_page::Random_Students(bool isclicked)
{
    Q_UNUSED(isclicked);
    //再读一次ini
    QSettings *m_IniFile = new QSettings("randomStudent.ini", QSettings::IniFormat);
    AllowDuplicate_ini = m_IniFile->value("RANDOM/AllowDuplicate").toInt();
    delete m_IniFile;
    int randomInt = QRandomGenerator::global()->bounded(0,student_count);
    qDebug()<< randomInt;
    if (students == nullptr)
    {
        ElaMessageBar::error(ElaMessageBarType::BottomRight, "failure", "未初始化名单!", 2000);
        return NULL;
    }
    qDebug()<< students[randomInt];
    QString tmp_log = log->text();
    if(AllowDuplicate_ini)//如果允许重复
    {
        Name->setText(students[randomInt]);
        tmp_log = tmp_log + students[randomInt] + "\t" ;
        log->setText(tmp_log);
    }else if(log_count>=student_count)
    {
        ElaMessageBar::error(ElaMessageBarType::TopLeft, "failure", "名单名额已满!", 2000);
    }else if(tmp_log.contains(students[randomInt])){//如果不允许重复，则检测是否包含在历史记录里
        Random_Students(true);//重随机一次
    }
    else{//如果不允许重复且未包含在历史记录里
        Name->setText(students[randomInt]);
        tmp_log = tmp_log + students[randomInt] + "\t" ;
        log->setText(tmp_log);
        log_count++;
    }
    return "success";
}

void Random_page::Random_Student_Five(bool isclicked)
{
    Q_UNUSED(isclicked);
    for(int i = 0; i<5; i++){
        Random_Students(isclicked);
    }
}


void Random_page::do_timeout()
{
    version_pre = tcpClient->readAll();
    do_AutoUpdate();
    timer->stop();
    tcpClient->disconnectFromHost();
    delete tcpClient;
}

bool Random_page::AutoUpdate(QString host_ip, QString remote_path, QString local_path, QString username, QString password)
{
    ElaMessageBar::information(ElaMessageBarType::BottomLeft, "Update", "正在检查更新!", 5000);
    tcpClient = new QTcpSocket();
    tcpClient->connectToHost("49.234.20.90",666);
    if(tcpClient->waitForConnected(10000))
    {
        tcpClient->write(("{COMMAND:CONNECT,client_type:"+QHostInfo::localHostName()+"}").toUtf8());
        tcpClient->write(("{COMMAND:SEND_DATA,client_type:"+QHostInfo::localHostName()+",data:VERSION}").toUtf8());
        timer = new QTimer(this); //this 为parent类, 表示当前窗口
        connect(timer, SIGNAL(timeout()), this, SLOT(do_timeout())); //计时结束触发
        timer->start(5000);
    }
    else
    {
        ElaMessageBar::error(ElaMessageBarType::BottomLeft, "Update", "未连接服务器!", 5000);
        delete tcpClient;
    }
    return 1;
}

void Random_page::do_AutoUpdate()
{
    int version_pre_int = 100*version_pre.mid(0,1).toInt()+10*version_pre.mid(2,1).toInt()+version_pre.mid(4,1).toInt();
    int version_int = 100*version.mid(0,1).toInt()+10*version.mid(2,1).toInt()+version.mid(4,1).toInt();
    if(version_pre_int > version_int)
    {
        qDebug()<<"版本需要更新!\n"<<"当前版本:"<<version<<"\n"<<"更新版本:"<<version_pre<<"\n";
        ElaMessageBar::error(ElaMessageBarType::BottomLeft, "Update", "版本需要更新!", 2000);
        ElaContentDialog* dialag = new ElaContentDialog(this);
        dialag->setLeftButtonText("下载");
        dialag->setMiddleButtonText("用用再说");
        dialag->setRightButtonText("退出");
        ElaText *warning = new ElaText("版本更新，是否下载？");
        dialag->setCentralWidget(warning);
        connect(dialag, &ElaContentDialog::rightButtonClicked, this, &Random_page::_closeEvent);
        // connect(dialag, SIGNAL(middleButtonClicked), this, SLOT());
        connect(dialag, SIGNAL(leftButtonClicked), this, SLOT(_update));
        dialag->show();

    }else
    {
        qDebug()<<"版本不需要更新!\n"<<"当前版本:"<<version<<"\n"<<"更新版本:"<<version_pre<<"\n";
        ElaMessageBar::success(ElaMessageBarType::BottomLeft, "Update", "版本不需要更新!", 2000);
    }
}
