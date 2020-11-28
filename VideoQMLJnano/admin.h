#include <QObject>
#include <QVector>
#include <QString>
#include <QMutex>

class Admin : public QObject
{

    Q_OBJECT
    public:
        Admin();
        ~Admin(){}
};
