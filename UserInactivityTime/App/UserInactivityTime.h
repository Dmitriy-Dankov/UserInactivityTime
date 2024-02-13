#ifndef USERINACTIVITYTIME_H
#define USERINACTIVITYTIME_H

#include <QObject>

class UserInactivityTime : public QObject
{
    Q_OBJECT
public:
    UserInactivityTime(const QString &username, const QString &time, QObject *parent = nullptr);

    void inactivityTime();
    void consoleHide();

signals:
    void messageIsReady(const QString&);

private:
    QString m_text;
    QString m_username;
    QString m_listTime;
    size_t m_sec{0};
    size_t m_min{0};
    void formAMessage();
    void setText(const QString &newText);
};

#endif // USERINACTIVITYTIME_H
