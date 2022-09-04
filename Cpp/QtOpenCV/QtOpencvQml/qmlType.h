#pragma once
#include <QDebug>
#include <QImage>

#include <QPainter>
#include <QtQuick>
#include <QObject>
#include <QQuickPaintedItem>


class qmlType :  public QQuickPaintedItem
{
   Q_OBJECT
    public:

    qmlType(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override; 

    void updateImage(const QImage& img);
    
    QImage *image;
};

