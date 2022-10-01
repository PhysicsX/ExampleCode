#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create an instance of a server and then start it.
    MyServer server;
    server.startServer();

    return a.exec();
}

// while true; do echo "ulas" | netcat localhost 1234 -w 1; sleep 0.1; done;
// echo "ulas" | netcat localhost 1234 -w 1
