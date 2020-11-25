#include <iostream>
#include <QDebug>
#include <QObject>
#include "helper.h"

Helper::Helper():QObject()
{

}

void Helper::hideSettings()
{
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

void Helper::setItem(QObject* it)
{
    item = it;
}

//void Helper::foo2()
//{
//    qDebug()<<"foo2() is called";
//}
