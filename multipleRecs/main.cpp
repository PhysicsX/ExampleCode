#include <QColor>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <unistd.h>
#include <QTimer>
#include <QRect>
#include <QRandomGenerator>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

struct Data
{
    Q_GADGET
    Q_PROPERTY(QRect rect MEMBER rect)
    Q_PROPERTY(QString text MEMBER text)
    Q_PROPERTY(QColor color MEMBER color)
public:
    QRect rect;
    QString text;
    QColor color;
    Data(const QRect& rect= QRect(), const QString& text="", const QColor& color = QColor(Qt::transparent)){
        this->rect = rect;
        this->text = text;
        this->color = color;
    }
};
Q_DECLARE_METATYPE(Data)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QByteArray jsonData;
    QFile file;
    file.setFileName("/home/jnano/Desktop/annotations.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonData = file.readAll();
    file.close();


    QJsonDocument search = QJsonDocument::fromJson(jsonData);
    //qDebug()<<search;
    QJsonArray jsonArray = search.array();
    QVector<int> x1;
    QVector<int> x2;
    QVector<int> y1;
    QVector<int> y2;

    for(auto it = jsonArray.constBegin(); it != jsonArray.constEnd(); ++it)
    {
        const QJsonValue &val = *it;
        //qDebug()<<val.toArray();
        QJsonObject obj = val[0].toObject();
        //qDebug()<<obj.value("x1");
        QJsonValue rVal = obj.value("x1");
        QVariant tmp = rVal.toVariant();
        //qDebug()<<tmp.toInt();
        x1.push_back(tmp.toInt());
        x2.push_back(obj.value("x2").toVariant().toInt());
        y1.push_back(obj.value("y1").toVariant().toInt());
        y2.push_back(obj.value("y2").toVariant().toInt());

    }


    QGuiApplication app(argc, argv);
    QVariantList rectlist;
    rectlist <<QVariant::fromValue( Data{ QRect{50, 30, 100, 100}, "text1", Qt::red});
   // rectlist <<QVariant::fromValue( Data{ QRect{200, 20, 30, 30 }, "text2", QColor("blue")});
   // rectlist <<QVariant::fromValue( Data{ QRect{300, 300, 200,33}, "text3", QColor(0, 200, 0)});
   // rectlist <<QVariant::fromValue( Data{ QRect{400, 23, 44, 55 }, "text4"});

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("rectlist", rectlist);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

int i{0};
QTimer timer;
QObject::connect(&timer, &QTimer::timeout, [&](){

    //int x = QRandomGenerator::global()->bounded(480);
    //int y = QRandomGenerator::global()->bounded(480);
    //int w = QRandomGenerator::global()->bounded(480);
    //int h = QRandomGenerator::global()->bounded(480);
    //qDebug()<<"x "<<x<<" y "<<y<<" w "<<w<<" h "<<h;

    rectlist.clear();
    rectlist <<QVariant::fromValue( Data{ QRect{x1[i] , y1[i] , (x2[i]-x1[i]), (y2[i]-y1[i]) }, "text1", Qt::red});
    i++;
    //rectlist <<QVariant::fromValue( Data{ QRect{x, y, 30, 30 }, "text2", QColor("blue")});
    //rectlist <<QVariant::fromValue( Data{ QRect{h, w, 200,33}, "text3", QColor(0, 200, 0)});
    //rectlist <<QVariant::fromValue( Data{ QRect{w, h, 44, 55 }, "text4"});
    engine.rootContext()->setContextProperty("rectlist", rectlist);

});

timer.start(200);



return app.exec();
}

#include "main.moc"
