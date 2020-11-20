#include <QObject>
#include <QVector>
#include <QString>

class WifiConf : public QObject
{

    Q_OBJECT
    public:
    Q_INVOKABLE void updateHotspot(QString name, QString pass);
    Q_INVOKABLE void connectToNetwork(QString name, QString pass);
    Q_INVOKABLE void reScan();

    Q_PROPERTY(bool enableHot READ getEnableHot WRITE setEnableHot NOTIFY enableHotChanged)
    Q_PROPERTY(QStringList ssidNames READ getSsidNames WRITE setSsidNames NOTIFY ssidNamesChanged)
    Q_PROPERTY(QString hotSpotPassword READ getHotSpotPassword  WRITE setHotSpotPassword NOTIFY hotSpotPasswordChanged)
    Q_PROPERTY(QString hotSpotSsid READ getHotSpotSsid WRITE setHotSpotSsid NOTIFY hotSpotSsidChanged)
    Q_PROPERTY(QString stationPassword READ getStationPassword  WRITE setStationPassword NOTIFY stationPasswordChanged)
    Q_PROPERTY(QString stationSsid READ getStationSsid WRITE setStationSsid NOTIFY stationSsidChanged)

    WifiConf();
    ~WifiConf(){};

    public slots:
    bool getEnableHot() const;
    QStringList getSsidNames() const;
    QString getHotSpotPassword() const;
    QString getHotSpotSsid() const;
    QString getStationPassword() const;
    QString getStationSsid() const;

    void setEnableHot(const bool flag);
    void setSsidNames(const QStringList list);
    void setHotSpotPassword(const QString pass);
    void setHotSpotSsid(const QString ssid);
    void setStationPassword(const QString pass);
    void setStationSsid(const QString ssid);

    signals:
    void enableHotChanged();
    void ssidNamesChanged();
    void hotSpotPasswordChanged();
    void hotSpotSsidChanged();
    void stationPasswordChanged();
    void stationSsidChanged();

    private:
    bool enableHot;
    QStringList ssidNames;
    QString hotSpotPassword;
    QString hotSpotSsid;
    QString stationPassword;
    QString stationSsid;

};
