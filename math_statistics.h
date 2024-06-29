#ifndef MATH_STATISTICS_H
#define MATH_STATISTICS_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include "ElaScrollPage.h"
#include "ElaIconButton.h"
#include "ElaPushButton.h"
#include "ElaSpinBox.h"
#include "ElaScrollPageArea.h"
#include "QHBoxLayout"
#include "ElaText.h"
#include "QVBoxLayout"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>


class math_statistics : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit math_statistics(QWidget *parent = nullptr);

private:
    /***UI界面***/
    QWidget *ui;

    /***题号***/
    int math_number[19] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

    /***SpinBox***/
    ElaSpinBox *spinboxes[19];


    /***ElaScrollPageArea***/
    ElaScrollPageArea *areas[19];

    /***QHBoxLayout***/
    QHBoxLayout *layouts[19];

    /***ElaText***/
    ElaText *question_numbers[19];

private slots:
    void on_clear_clicked(bool isClicked)
    {
        for(int i = 0;i<19;i++)
        {
            spinboxes[i]->setValue(0);
        }
    }
    void on_export_data_button_clicked(bool isClicked);

signals:
};

#endif // MATH_STATISTICS_H
