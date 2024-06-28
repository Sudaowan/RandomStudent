#ifndef ABOUT_H
#define ABOUT_H

#include <QObject>
#include <QWidget>
#include "ElaText.h"
#include "ElaScrollPage.h"

class about : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit about(QWidget *parent = nullptr);

private:
    ElaText *text;
    QWidget *ui;

    ElaText *log;

signals:
};

#endif // ABOUT_H
