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
        item->setProperty("z",41);
        QTimer::singleShot(5000,this,[&](){

                if(item->property("visible").toBool())
                {
                    item->setProperty("visible",false);
                    item->setProperty("z",-1);
                }
        });
    }
}

void MyClass::setItem(QObject* it)
{
    item = it;
}

void MyClass::foo2()
{
    qDebug()<<"foo2() is called";
}
