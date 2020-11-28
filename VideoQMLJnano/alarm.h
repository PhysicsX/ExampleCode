#include <QObject>
#include <QVector>
#include <QString>
#include <QMutex>

class Alarm : public QObject
{

    Q_OBJECT
    public:
        Alarm();
        ~Alarm(){}
};
