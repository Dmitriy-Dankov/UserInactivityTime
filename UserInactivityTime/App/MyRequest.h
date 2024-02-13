#ifndef MYREQUEST_H
#define MYREQUEST_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class MyRequest : public QObject
{
    Q_OBJECT
public:
    MyRequest(const QString &token, const QString &id_chat,  QObject *parent = nullptr);

    void sendMessage(const QString& text);

private:
    QNetworkAccessManager *m_manager = nullptr;
    QNetworkReply *m_reply = nullptr;
    QString m_url;
};

#endif // MYREQUEST_H
