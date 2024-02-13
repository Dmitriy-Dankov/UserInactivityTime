#include <QCoreApplication>
#include <QSettings>
#include <QThread>
#include "UserInactivityTime.h"
#include "MyRequest.h"

int main(int argc, char *argv[])
{
    QSettings settings ("config.ini", QSettings::IniFormat);
    settings.beginGroup("/Settings");
    QString token = settings.value("/token").toString();
    QString id_chat = settings.value("/id_chat").toString();
    QString inTime = settings.value("/inactive_time").toString();
    QString username = settings.value("/username").toString();
    settings.endGroup();

    QCoreApplication a(argc, argv);

    UserInactivityTime uit(username, inTime);
    uit.consoleHide();

    MyRequest request(token, id_chat);
    //request.sendMessage("User " + username + " turned on the computer");

    QObject::connect(&uit, &UserInactivityTime::messageIsReady, &request, &MyRequest::sendMessage);

    QThread thread;
    QObject::connect(&thread, &QThread::started, &uit, &UserInactivityTime::inactivityTime);    
////////////// A window procedure is required to implement this snippet //////////////
//    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&](){
//        qDebug() << "end";
//        thread.quit();
//        request.sendMessage("User " + username + " turned off the computer");
//    });
//////////////////////////////////////////////////////////////////////////////////////
    uit.moveToThread(&thread);
    thread.start();

    int nResult = a.exec();

    thread.quit();
    return nResult;
};

