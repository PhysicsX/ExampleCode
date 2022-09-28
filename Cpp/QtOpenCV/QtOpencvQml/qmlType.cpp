#include "qmlType.h"

qmlType::qmlType(QQuickItem *parent):QQuickPaintedItem(parent)
{
        image = new QImage(100,100,QImage::Format_RGB32);
        image->fill(QColor("yellow"));

    // If camera is open here, it is not possible to send the frames.
    // need another thread to send the frames over this class
}

void qmlType::paint(QPainter *painter) {
	painter->drawImage(this->boundingRect(), *image);
} 

void qmlType::updateImage(const QImage& img)
{
	*image = img;
	update();
}

