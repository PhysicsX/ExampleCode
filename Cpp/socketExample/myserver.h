// myserver.h

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QThreadPool>

#include "myclient.h"

class MyServer : public QTcpServer
{
    // Q_OBJECT is the base class for all qt libraries
    Q_OBJECT
    QThreadPool *pool; // this can be used also global isntead of dependency injection
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:

public slots:

};

#endif // MYSERVER_H
