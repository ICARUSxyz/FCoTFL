#include "screenfactor.h"
#include <QScreen>
#include <QApplication>

ScreenFactor::ScreenFactor(QObject *parent) : QObject(parent)
{

}

double ScreenFactor::getScreenFactor()
{

    QScreen *screen = qApp->primaryScreen();
    const int baseValue = 90;    
    qreal dpiVal = screen->logicalDotsPerInch();
    qreal dpiVal = screen->devicePixelRatio();

    //qDebug() << dpiVal << ratioVal;
    screenFactor = dpiVal * ratioVal / baseValue;
    return screenFactor;
}
