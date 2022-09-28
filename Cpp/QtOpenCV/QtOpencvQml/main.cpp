#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QImage>

#include <QPainter>

#include <QObject>
#include <QQuickPaintedItem>
#include "qmlType.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qRegisterMetaType<cv::Mat>("cv::Mat");
    qmlRegisterType<qmlType>("Painter", 1, 0, "QmlType");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    engine.load(url);
    QObject *object = engine.rootObjects()[0];

    QObject *inputCamera = object->findChild<QObject*>("inputCamera");

    qmlType *ptrQmlType = qobject_cast<qmlType*>(inputCamera);
    
    QTimer timer;
	
    cv::VideoCapture cap("/home/b.mp4");
    
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {

	cv::Mat frame;	
	cap >> frame;
	
        if(frame.empty())
	{
		// to clean lsat frame
		int width = 100;
		int height = 200;
		QImage image = QPixmap(width, height).toImage();
		
		ptrQmlType->updateImage(image);
		timer.stop();
        	return;
	}
	// Opencv use BGR but QImage use RGB so color information
	// should be swapped for this case Mat->QImage
	// no need to swap when Mat->QImage->Mat
	cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);	
	QImage imgIn= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	//.rgbSwapped();

 	ptrQmlType->updateImage(imgIn);

    }
    );
    timer.start(60);
 
    return app.exec();
}
