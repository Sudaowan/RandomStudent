#include <QApplication>
#include "ElaApplication.h"
#include "ElaWindow.h"
#include "random_page.h"
#include "settings.h"
#include "about.h"
#include "math_statistics.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ElaApplication::getInstance()->init();
    ElaWindow w;

    w.setWindowTitle("抽签模拟器");
    QIcon ico(":/icon/image/lucky_block.ico");
    w.setWindowIcon(ico);

    w.setUserInfoCardPixmap((QPixmap)":/icon/image/lucky_block.png");
    w.setUserInfoCardTitle("By-Sudaowan");
    w.setUserInfoCardSubTitle("Email:Sudaowan@163.com");

    Random_page *r_page;
    r_page = new Random_page(nullptr,&w);
    w.addPageNode("Random",r_page,ElaIconType::BlockQuestion);

    settings *set_page;
    set_page = new settings();
    w.addPageNode("Setting",set_page,ElaIconType::GearComplex);

    QString statistics_key1;
    w.addExpanderNode("Statistics",statistics_key1,ElaIconType::PenSwirl);
    math_statistics *math_page = new math_statistics();
    w.addPageNode("Math",math_page,statistics_key1,ElaIconType::CalculatorSimple);

    about *about_page;
    about_page = new about();
    w.addPageNode("About",about_page,ElaIconType::Citrus);

    w.show();
    return a.exec();
}


