#include <QCoreApplication>
#include "firebase.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    firebase fbHandler;


    return a.exec();
}
