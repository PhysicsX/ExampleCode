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
#include "helper.h"
#include "networkManager.h"
#include "wifiConf.h"
#include <thread>
#include "admin.h"

#define QT_NO_DEBUG_OUTPUT
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<NetworkManager>("com.ulasdikme.networkManager",1,0,"NetworkManager");
    qmlRegisterType<WifiConf>("com.ulasdikme.wifiConf",1,0,"WifiConf");
    qmlRegisterType<WifiConf>("com.ulasdikme.admin",1,0,"Admin");
    qmlRegisterType<WifiConf>("com.ulasdikme.local",1,0,"Local");
    qmlRegisterType<WifiConf>("com.ulasdikme.alarm",1,0,"Alarm");


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

    Helper helper;

    helper.setItem(item2);

    QObject::connect(item,SIGNAL(qmlSignal()),&helper,SLOT(hideSettings()));


    QObject* item3 = NULL;
    item3 = engine.rootObjects().at(0)->findChild<QQuickItem*>("passTextField");
    if(item3 == NULL)
        qDebug()<<"NUL3";


    //MyClass myClass2; //experimental
    //myClass2.setItem(item4);
    //QObject::connect(item3,SIGNAL(editingFinished()),&myClass2,SLOT(foo2()));


    auto rootObj = engine.rootObjects().at(0); //assume main.qml is loaded

    QObject* catagory = rootObj->findChild<QObject *>("pageModel2");

    qDebug()<<catagory->property("count");


    //start device as a hotspot
    QProcess process;
    process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
    if(!process.waitForFinished())
        qDebug()<<"can not get hotspot name";
    QString p_stdout = process.readAllStandardOutput();
    qDebug()<<p_stdout;
    process.start("bash", QStringList()<<"-c"<<"nmcli connection delete id'"+p_stdout+"'");
    if(!process.waitForFinished())
        qDebug()<<"can not delete connection hotspot";
    process.start("bash", QStringList()<<"-c"<<"nmcli r wifi off"); // enable wifi
    if(!process.waitForFinished())
        qDebug()<<"wifi can not off, check wifi hardware is exist";

    process.start("bash", QStringList()<<"-c"<<"nmcli r wifi on"); // enable wifi
    if(!process.waitForFinished())
        qDebug()<<"wifi can not started, check wifi hardware is exist";


    std::thread t([](){

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        QProcess process;
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

    });
    t.detach();


//    QTimer::singleShot(2000,[&](){
//        QProcess process;
//        process.start("bash", QStringList()<<"-c"<<"nmcli dev wifi hotspot ifname wlan0 ssid EPILOG_AP password 'epilog2020'");
//        if(process.waitForFinished())
//            qDebug()<<"Hotspot is created";
//        else
//            qDebug()<<"Hotspot can not be created";

//        process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
//        if(!process.waitForFinished())
//            qDebug()<<"can not get hotspot name";
//        QString p_stdout = process.readAllStandardOutput();
//        qDebug()<<p_stdout;
//        QString hotspot = "Hotspot";
//        if(p_stdout.contains(hotspot, Qt::CaseInsensitive))
//        {
//            QString cmd = "nmcli con up"+hotspot;
//            process.start("bash", QStringList()<<"-c"<<cmd);
//            if(!process.waitForFinished())
//                qDebug()<<"Hotspot can not bring up";
//        }
//        else
//        {
//            qDebug()<<"Hotspot name can not find";
//        }

//    });

    return app.exec();
}
