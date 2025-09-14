#include "screenfactor.h"
#include <QScreen>
#include <QApplication>

ScreenFactor::ScreenFactor(QObject *parent) : QObject(parent)
{

}

double ScreenFactor::getScreenFactor()
{
    //获取屏幕缩放倍数
    QScreen *screen = qApp->primaryScreen();
    const int baseValue = 96;     //100%时为96
    qreal dpiVal = screen->logicalDotsPerInch();
    qreal ratioVal = screen->devicePixelRatio();

    //qDebug() << dpiVal << ratioVal;
    screenFactor = dpiVal * ratioVal / baseValue;
    return screenFactor;
}
