#include "settings.h"

settings::settings(QWidget *parent)
    : ElaScrollPage(parent)
{
    ui = new QWidget(this);
    ui->setWindowTitle("◎设置");
    //screwdriverWrench or GearComplex

    encipher_title = new ElaText();
    encipher_title->setTextSize(16);
    encipher_title->setText("●加密/解密名单文件:");
    input_key = new ElaLineEdit();
    input_key->setPlaceholderText(tr("加密/解密文件 请输入密钥:"));
    input_key->setEchoMode(QLineEdit::Password);
    input_key->setFixedWidth(450);
    pushBtn_encryption = new ElaIconButton(ElaIconType::Lock);
    pushBtn_encryption->setText("加密文件");
    pushBtn_encryption->setMinimumSize(200,50);
    pushBtn_decryption = new ElaIconButton(ElaIconType::LockOpen);
    pushBtn_decryption->setText("解密文件");
    pushBtn_decryption->setMinimumSize(200,50);

    chkBox_allow_duplicates = new ElaCheckBox("允许重复",this);

    QSettings *m_IniFile = new QSettings("randomStudent.ini", QSettings::IniFormat);
    int AllowDuplicate_ini = m_IniFile->value("RANDOM/AllowDuplicate").toInt();
    qDebug() << "RANDOM/AllowDuplicate_ini value:" << AllowDuplicate_ini;
    chkBox_allow_duplicates->setChecked((bool)AllowDuplicate_ini);

    ElaScrollPageArea* checkBoxArea = new ElaScrollPageArea(this);
    QHBoxLayout* checkBoxLayout = new QHBoxLayout(checkBoxArea);
    ElaText* checkBoxText = new ElaText("基础设置", this);
    checkBoxText->setTextSize(15);
    checkBoxLayout->addWidget(checkBoxText);
    checkBoxLayout->addWidget(chkBox_allow_duplicates);
    checkBoxLayout->addStretch();

    QHBoxLayout *layoutBtn = new QHBoxLayout();
    layoutBtn->addWidget(pushBtn_encryption);
    layoutBtn->addWidget(pushBtn_decryption);
    layoutBtn->addStretch();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(encipher_title);
    layout->addWidget(input_key);
    layout->addLayout(layoutBtn);
    layout->addWidget(checkBoxArea);
    layout->addStretch();

    ui->setLayout(layout);
    addCentralWidget(ui);

    connect(pushBtn_encryption,SIGNAL(clicked(bool)),this,SLOT(do_pushBtn_encryption(bool)));
    connect(pushBtn_decryption,SIGNAL(clicked(bool)),this,SLOT(do_pushBtn_decryption(bool)));
    connect(chkBox_allow_duplicates,SIGNAL(clicked(bool)),this,SLOT(do_chkBox_allow_duplicates(bool)));


}

settings::~settings()
{

}

bool settings::identify(){
    QString key = input_key->text();
    if(key == "Sudaowan555")
        return true;
    else
        return false;
}

void settings::do_pushBtn_encryption(bool isclicked)
{
    Q_UNUSED(isclicked);
    if(identify())
    {
        QFile f("list.txt");
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ElaMessageBar::error(ElaMessageBarType::BottomLeft, " ", "打开文件失败!", 2000);
        }
        QTextStream txtInput(&f);
        QFile f_w("Student.studentData");
        if(!f_w.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ElaMessageBar::error(ElaMessageBarType::BottomLeft, " ", "创建studentData文件失败!", 2000);
        }
        QTextStream txtOutput(&f_w);
        QByteArray str;
        while(!txtInput.atEnd())
        {
            str = txtInput.readLine().toUtf8();
            txtOutput << str.toBase64() << Qt::endl;
        }
        f_w.close();
        f.close();
        ElaMessageBar::success(ElaMessageBarType::BottomLeft, "success", "加密成功!", 2000);
        //测试:
        // QByteArray pwd = _encipher->encryption("我是孟锦程");
        // qDebug()<< pwd;
        // QByteArray content = _encipher->deciphering(pwd);
        // qDebug()<< (QString)content;
    }
    else
        ElaMessageBar::error(ElaMessageBarType::BottomLeft, " ", "密钥错误!", 2000);

}

void settings::do_pushBtn_decryption(bool isclicked)
{
    Q_UNUSED(isclicked);
    if(identify())
    {
        QFile f("Student.studentData");
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ElaMessageBar::error(ElaMessageBarType::BottomLeft, " ", "打开文件失败!", 2000);
        }
        QTextStream txtInput(&f);
        QFile f_w("list.txt");
        if(!f_w.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ElaMessageBar::error(ElaMessageBarType::BottomLeft, " ", "创建txt文件失败!", 2000);
        }
        QTextStream txtOutput(&f_w);
        QByteArray str;
        while(!txtInput.atEnd())
        {
            str = txtInput.readLine().toUtf8();
            txtOutput << QByteArray::fromBase64(str) << Qt::endl;
        }
        f_w.close();
        f.close();
        ElaMessageBar::success(ElaMessageBarType::BottomLeft, "success", "解密成功!", 2000);
    }
    else
        ElaMessageBar::error(ElaMessageBarType::BottomLeft, " ", "密钥错误!", 2000);
}

void settings::do_chkBox_allow_duplicates(bool ischecked)
{

    QSettings *m_IniFile = new QSettings("randomStudent.ini", QSettings::IniFormat);
    m_IniFile->beginGroup("RANDOM");     // 设置当前节名，代表以下的操作都是在这个节中
    m_IniFile->setValue( "AllowDuplicate",(int)ischecked); // 因为上面设置了节了，这里不在需要把节名写上去
    m_IniFile->endGroup();                   // 结束当前节的操作
    delete m_IniFile;
}
