#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQuickView>
#include <QQuickItem>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QAbstractListModel>
#include <QQmlProperty>
#include <QVariant>
#include <QProcess>
#include "myclass.h"
#include "networkManager.h"


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<NetworkManager>("com.ulasdikme.networkManager",1,0,"NetworkManager");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    QObject* item = NULL;
    item = engine.rootObjects().at(0)->findChild<QQuickItem*>("streaming");
    if(item == NULL)
        qDebug()<<"NUL";

     QObject* item2 = NULL;
     item2 = engine.rootObjects().at(0)->findChild<QQuickItem*>("settings");
        if(item2 == NULL)
            qDebug()<<"NUL";

    MyClass myClass;
    QTimer timer;
    myClass.setItem(item2);

    QObject::connect(item,SIGNAL(qmlSignal()),&myClass,SLOT(foo()));


    QObject* item3 = NULL;
    item3 = engine.rootObjects().at(0)->findChild<QQuickItem*>("passTextField");
    if(item3 == NULL)
        qDebug()<<"NUL3";


    MyClass myClass2; //experimental
    //myClass2.setItem(item4);
    QObject::connect(item3,SIGNAL(editingFinished()),&myClass2,SLOT(foo2()));


    auto rootObj = engine.rootObjects().at(0); //assume main.qml is loaded

    QObject* catagory = rootObj->findChild<QObject *>("pageModel2");

    qDebug()<<catagory->property("count");


    //start device as a hotspot
    QProcess process;
    process.start("bash", QStringList()<<"-c"<<"nmcli r wifi on"); // enable wifi
    if(!process.waitForFinished())
        qDebug()<<"wifi can not started, check wifi hardware is exist";


    process.start("bash", QStringList()<<"-c"<<"nmcli dev wifi hotspot ifname wlan0 ssid EPILOG_AP password 'epilog2020'");
    if(process.waitForFinished())
        qDebug()<<"Hotspot is created";
    else
        qDebug()<<"Hotspot can not be created";


    process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
    if(!process.waitForFinished())
        qDebug()<<"can not get hotspot name";
    QString p_stdout = process.readAllStandardOutput();
    qDebug()<<p_stdout;
    QString hotspot = "Hotspot";
    if(p_stdout.contains(hotspot, Qt::CaseInsensitive))
    {
        QString cmd = "nmcli con up"+hotspot;
        process.start("bash", QStringList()<<"-c"<<cmd);
        if(!process.waitForFinished())
            qDebug()<<"Hotspot can not bring up";
    }
    else
    {
        qDebug()<<"Hotspot name can not find";
    }








    return app.exec();
}
