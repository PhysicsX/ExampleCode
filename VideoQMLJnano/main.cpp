#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQuickView>
#include <QQuickItem>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include "myclass.h"

void foo()
{

}
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

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
    item3 = engine.rootObjects().at(0)->findChild<QQuickItem*>("back");
    if(item3 == NULL)
        qDebug()<<"NUL3";


QObject* item4 = NULL;
item4 = engine.rootObjects().at(0)->findChild<QQuickItem*>("password");
if(item4 == NULL)
    qDebug()<<"NUL4";

    MyClass myClass2; //experimental
    myClass2.setItem(item4);
    QObject::connect(item3,SIGNAL(qmlSignalPass()),&myClass2,SLOT(foo2()));

    //QObject::connect(item,SIGNAL(qmlSignal()),[=](){qDebug()<<"asasda";});
    //QTimer::singleShot(5000,&app,[](){
    //});

    return app.exec();
}