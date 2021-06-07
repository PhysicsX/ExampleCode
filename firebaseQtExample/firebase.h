#ifndef FIREBASE_H
#define FIREBASE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class firebase : public QObject
{
    Q_OBJECT
public:
    explicit firebase(QObject *parent = nullptr);
    ~firebase();

public slots:
    void NetworkReplyRead();

signals:
private:

    QNetworkAccessManager *m_networkManager;
    QNetworkReply * m_networkReply;
};

#endif
