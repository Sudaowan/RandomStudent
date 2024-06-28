#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QWidget>
#include "ElaIconButton.h"
#include "ElaCheckBox.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QFile>
#include "ElaMessageBar.h"
#include "ElaScrollPageArea.h"
#include "ElaScrollPage.h"
#include "ElaLineEdit.h"
#include "ElaText.h"
#include "QSettings"

class settings : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

private:
    QWidget *ui;

    ElaText *encipher_title;
    ElaLineEdit *input_key;
    ElaIconButton *pushBtn_encryption;
    ElaIconButton *pushBtn_decryption;
    ElaCheckBox *chkBox_allow_duplicates;

    bool identify();

private slots:
    void do_pushBtn_encryption(bool isclicked);
    void do_pushBtn_decryption(bool isclicked);
    void do_chkBox_allow_duplicates(bool ischecked);

signals:
};

#endif // SETTINGS_H
