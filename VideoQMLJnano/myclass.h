#include<QObject>
#include <QTimer>

class MyClass : public QObject
{
public:
    Q_OBJECT
        public slots:
        void foo();
        void foo2();

        public:
        void setItem(QObject* it);
        QTimer timer;
        QObject* item;
        MyClass();
        ~MyClass(){};
};