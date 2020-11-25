#include <QObject>
#include <QTimer>

class Helper : public QObject
{
public:
    Q_OBJECT
        public slots:
        void hideSettings();
        //void foo2();

        public:
        void setItem(QObject* it);
        QTimer timer;
        QObject* item;
        Helper();
        ~Helper(){};
};
