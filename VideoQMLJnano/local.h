#include <QObject>
#include <QVector>
#include <QString>
#include <QMutex>

class Local : public QObject
{

    Q_OBJECT
    public:
        Local();
        ~Local(){}
};
