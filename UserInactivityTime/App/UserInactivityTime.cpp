#include "UserInactivityTime.h"
#include <windows.h>
#include <qthread.h>
//#include <QDebug>

UserInactivityTime::UserInactivityTime(const QString &username, const QString &time, QObject *parent)
    : QObject{parent}, m_username{username}
{
    QStringList list = time.split(',');
    for (auto str : list ) {
        m_listTime += str.trimmed();
    }
}

void UserInactivityTime::inactivityTime()
{
    tagLASTINPUTINFO curr{sizeof(LASTINPUTINFO), 0};
    tagLASTINPUTINFO last{};

    GetLastInputInfo(&curr);
    last = curr;

    QString str;
    size_t lastEvent;

    int msec = 990;
    while (1) {
        QThread::usleep (msec * 1000);

        GetLastInputInfo(&curr);

        lastEvent = (curr.dwTime - last.dwTime) / 1000;

        if (lastEvent > 0) {
            m_sec = m_min = 0;
        } else {
            if (m_sec + 1 == 60) { ++m_min; m_sec = 0; }
            else ++m_sec;
        }

        //////////////////// Debug information ////////////////////
//            if (m_sec != 0) {
//                str = QString("%1 min, %2 sec").arg(m_min).arg(m_sec);
//            } else if (m_sec == 0 && m_min > 0) {
//                str = QString("%1 min, %2 sec").arg(m_min).arg(m_sec);
//            }
//            qDebug() << str;
        ///////////////////////////////////////////////////////////

        formAMessage();

        last = curr;

        str.clear();
    }
}

void UserInactivityTime::consoleHide()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void UserInactivityTime::setText(const QString &newText)
{
    m_text = newText;
    emit messageIsReady(m_text);
}

void UserInactivityTime::formAMessage()
{
    for (auto str : m_listTime ) {
        if(str == QString::number(m_min) && m_sec == 0) {
            setText(QString("User inactivity time %1: %2 min").arg(m_username).arg(m_min));
            return;
        }
    }
}
