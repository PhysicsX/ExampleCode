#include "firebase.h"
#include <QNetworkRequest>
#include <QDebug>

firebase::firebase(QObject *parent):QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
    //m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://example-72273-default-rtdb.europe-west1.firebasedatabase.app/Pets/One.json")));
    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://google.com")));

    connect(m_networkReply, &QNetworkReply::finished, this, &firebase::NetworkReplyRead);
}

firebase::~firebase()
{
    m_networkManager->deleteLater();
}

void firebase::NetworkReplyRead()
{
    qDebug()<<m_networkReply->readAll();
}

