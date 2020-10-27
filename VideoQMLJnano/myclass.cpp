#include <iostream>
#include <QDebug>
#include <QObject>
#include "myclass.h"

MyClass::MyClass():QObject()
{

}

void MyClass::foo()
{
    qDebug()<<"foo() is called";
    if(!item->property("visible").toBool())
    {
        item->setProperty("visible",true);
        QTimer::singleShot(5000,this,[&](){

                if(item->property("visible").toBool())
                    item->setProperty("visible",false);

        });
    }
}

void MyClass::setItem(QObject* it)
{
    item = it;
}
