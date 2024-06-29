#include "math_statistics.h"

math_statistics::math_statistics(QWidget *parent)
    : ElaScrollPage(parent)
{
    ui = new QWidget();
    ui->setWindowTitle("◎数学错题统计");
    QVBoxLayout *layout_total = new QVBoxLayout();

    ElaPushButton *clear_button = new ElaPushButton();
    clear_button->setText("清空统计");
    clear_button->setMinimumWidth(200);
    ElaPushButton *export_data_button = new ElaPushButton();
    export_data_button ->setText("显示柱状图");
    export_data_button->setMinimumWidth(200);

    connect(clear_button,SIGNAL(clicked(bool)),this,SLOT(on_clear_clicked(bool)));
    connect(export_data_button,SIGNAL(clicked(bool)),this,SLOT(on_export_data_button_clicked(bool)));

    QHBoxLayout *btn_layout = new QHBoxLayout();//用于存放上面两个按钮
    btn_layout->addWidget(clear_button);
    btn_layout->addWidget(export_data_button);
    layout_total->addLayout(btn_layout);

    for(int i = 0;i<19;i++)
    {
        /***初始化***/
        spinboxes[i] = new ElaSpinBox(this);
        areas[i] = new ElaScrollPageArea(this);
        layouts[i] = new QHBoxLayout(areas[i]);
        question_numbers[i] = new ElaText(QString::number(math_number[i]),this);

        /***属性设置***/
        question_numbers[i]->setTextSize(15);
        spinboxes[i]->setMinimum(0);
        spinboxes[i]->setSingleStep(1); // 步长
        spinboxes[i]->setValue(0);  // 起始默认值

        layouts[i]->addWidget(question_numbers[i]);
        layouts[i]->addStretch(5);
        layouts[i]->addWidget(spinboxes[i]);
        layouts[i]->addStretch();


        layout_total->addWidget(areas[i]);
        layout_total->addStretch();


    }
    ui->setLayout(layout_total);
    addCentralWidget(ui);

}

void math_statistics::on_export_data_button_clicked(bool isClicked)
{
    QMainWindow *chart_page = new QMainWindow();

    /***添加数据集***/
    QBarSet *set = new QBarSet("Numbers");
    for (int i =0;i<19;i++)
    {
        *set << spinboxes[i]->value();
    }

    /***整合进包里***/
    QBarSeries *series = new QBarSeries();
    series->append(set);

    /***建立新图表***/
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("错题数据统计柱形图");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    /***添加坐标轴***/
    QStringList categories;
    for (int i =0;i<19;i++)
    {
        categories << "第"+QString::number(math_number[i])+"题";
    }
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    //QBarCategoryAxis类将类别添加到图表的轴中。
    //可以设置QBarCategoryAxis来显示带有标记、网格线和阴影的轴线。在刻度之间绘制类别。
    axis->append(categories);
    chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
    chart->setAxisX(axis, series);//设置坐标轴

    chart->legend()->setVisible(true); //设置图例为显示状态
    chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    chart_page->setCentralWidget(chartView);
    chart_page->resize(1200, 600);

    chart_page->show();
}
