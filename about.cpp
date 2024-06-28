#include "about.h"
#include "QVBoxLayout"

about::about(QWidget *parent)
    : ElaScrollPage(parent)
{
    ui = new QWidget();

    ui->setWindowTitle("关于");

    text = new ElaText();
    text->setTextSize(20);
    text->setText("感谢ElaWidget第三方库支持!\n"
                  "本项目由2022级Sudaowan(Github Name)同学编写,语言:Qt(C++)\n"
                  "项目已经在Github上开源,遵循MIT License\n"
                  "作者联系方式:(QQ)2148684795,(email)Sudaowan@163.com");
    log = new ElaText();
    log->setTextSize(20);
    log->setText("更新日志:\n"
                 "2024.06.24:更新ini文件,更新了“允许重复”选项\n"
                 "2024.06.22:更新Setting界面,提供学生名单加密算法,更新About界面。\n"
                 "2024.06.21:更新基础UI界面和Random页面。\n");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(text);
    layout->addStretch(10);
    layout->addWidget(log);
    layout->addStretch(100);
    ui->setLayout(layout);
    addCentralWidget(ui);
}
