// myclient.cpp

#include "myclient.h"

MyClient::MyClient(QObject *parent, QThreadPool* _pool) :
    QObject(parent)
{
    pool = _pool;
    //QThreadPool::globalInstance()->setMaxThreadCount(5);
}

void MyClient::setSocket(qintptr descriptor)
{
    // make a new socket
    socket = new QTcpSocket(this);

    qDebug() << "A new socket created!";

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);

    qDebug() << " Client connected at " << descriptor;
}


// asynchronous - runs separately from the thread we created
void MyClient::connected()
{
    qDebug() << "Client connected event";
}

// asynchronous
void MyClient::disconnected()
{
    qDebug() << "Client disconnected";
}

// Our main thread of execution
// This happening via main thread
// Our code running in our current thread not in another QThread
// That's why we're getting the thread from the pool

void MyClient::readyRead()
{
    qDebug() << "MyClient::readyRead()";
    qDebug() << socket->readAll();

    // Time consumer
    MyTask *mytask = new MyTask();
    // mytask->setAutoDelete(true);

    // using queued connection
    connect(mytask, SIGNAL(Result(int)), this, SLOT(TaskResult(int)), Qt::QueuedConnection);

    qDebug() << "Starting a new task using a thread from the QThreadPool";

    // QThreadPool::globalInstance() returns global QThreadPool instance
    // QThreadPool::globalInstance()->start(mytask);
    pool->start(mytask);

}

// After a task performed a time consuming task,
// we grab the result here, and send it to client
void MyClient::TaskResult(int Number)
{
    QByteArray Buffer;
    Buffer.append("\r\nTask result = ");
    Buffer.append(QString::number(Number));

    socket->write(Buffer);
    socket->flush();
    socket->deleteLater();
}
