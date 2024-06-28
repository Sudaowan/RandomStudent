﻿#ifndef ELAWINDOW_H
#define ELAWINDOW_H

#include <Windows.h>

#include <QAbstractNativeEventFilter>
#include <QWidget>

#include "Def.h"
#include "stdafx.h"
class ElaWindowPrivate;
class ElaNavigationBar;
class QStackedWidget;
class ELA_EXPORT ElaWindow : public QWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaWindow)
    Q_PROPERTY_CREATE_Q_H(int, ThemeChangeTime)
    Q_PROPERTY_CREATE_Q_H(ElaNavigationType::NavigationDisplayMode, NavigationBarDisplayMode)

public:
    explicit ElaWindow(QWidget* parent = nullptr);
    ~ElaWindow();

    void setIsNavigationBarEnable(bool isEnable);
    bool getIsNavigationBarEnable() const;
    void setWindowTitle(QString title);
    void setIsStayTop(bool isStayTop);
    bool getIsStayTop() const;
    void setIsFixedSize(bool isFixedSize);
    bool getIsFixedSize() const;
    void setUserInfoCardVisible(bool isVisible);
    void setUserInfoCardPixmap(QPixmap pix);
    void setUserInfoCardTitle(QString title);
    void setUserInfoCardSubTitle(QString subTitle);
    ElaNavigationType::NodeOperateReturnType addExpanderNode(QString expanderTitle, QString& expanderKey, ElaIconType awesome = ElaIconType::None) const;
    ElaNavigationType::NodeOperateReturnType addExpanderNode(QString expanderTitle, QString& expanderKey, QString targetExpanderKey, ElaIconType = ElaIconType::None) const;
    ElaNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, ElaIconType awesome = ElaIconType::None) const;
    ElaNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, ElaIconType awesome = ElaIconType::None) const;
    ElaNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, int keyPoints = 0, ElaIconType awesome = ElaIconType::None) const;
    ElaNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, int keyPoints = 0, ElaIconType awesome = ElaIconType::None) const;
    ElaNavigationType::NodeOperateReturnType addFooterNode(QString footerTitle, QString& footerKey, int keyPoints = 0, ElaIconType awesome = ElaIconType::None) const;
    ElaNavigationType::NodeOperateReturnType addFooterNode(QString footerTitle, QWidget* page, QString& footerKey, int keyPoints = 0, ElaIconType awesome = ElaIconType::None) const;

    void navigation(QString pageKey);
    void setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true);
    void setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags);
    ElaAppBarType::ButtonFlags getWindowButtonFlags() const;

    void setIsDefaultClosed(bool isDefaultClosed);
    bool getIsDefaultClosed() const;
    void closeWindow();
Q_SIGNALS:
    Q_SIGNAL void userInfoCardClicked();
    Q_SIGNAL void footerNodeClicked(QString footerKey); // 页脚没有绑定页面时发送
    Q_SIGNAL void closeButtonClicked();

protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    friend class ElaNavigationBarPrivate;
};

#endif // ELAWINDOW_H
