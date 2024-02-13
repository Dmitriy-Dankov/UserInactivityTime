#include "MyRequest.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

MyRequest::MyRequest(const QString &token, const QString &id_chat, QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager(this);
    m_url = "https://api.telegram.org/bot" + token + "/sendMessage?chat_id=" + id_chat;
}

void MyRequest::sendMessage(const QString &text)
{
    m_reply = m_manager->get(QNetworkRequest(m_url + "&text=" + text));

    QEventLoop loop;
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    m_reply->deleteLater();
    m_reply = nullptr;
}
