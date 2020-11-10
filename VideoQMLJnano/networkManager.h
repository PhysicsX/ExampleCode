#include <QObject>
#include <QTimer>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void applyNetwork(bool arg1, bool arg2);
    Q_INVOKABLE void setStaticConf(QString ip, QString mask, QString gateway);
    Q_PROPERTY(QString ipAddr READ getIpAddr WRITE setIpAddr NOTIFY ipAddrChanged)
    Q_PROPERTY(QString routerAddr READ getRouterAddr WRITE setRouterAddr NOTIFY routerAddrChanged)
    Q_PROPERTY(QString maskAddr READ getMaskAddr WRITE setMaskAddr NOTIFY maskAddrChanged)
    Q_PROPERTY(bool enableDHCP READ getEnableDHCP WRITE setEnableDHCP NOTIFY enableDHCPChanged)

         public slots:
         public:
         void setIpAddr(const QString &ip);
         void setRouterAddr(const QString &router);
         void setMaskAddr(const QString &mask);
         void setEnableDHCP(const bool flag);
         QString getRouterAddr() const;
         QString getIpAddr() const;
         QString getMaskAddr() const;
         bool getEnableDHCP() const;
         NetworkManager();
        ~NetworkManager(){};
        public slots:
        bool setIp();
        //bool setRouter();
        bool setDHCP();
        bool setStatic();
    signals:
        void ipAddrChanged();
        void routerAddrChanged();
        void maskAddrChanged();
        void enableDHCPChanged();
    private:
        QString m_ipAddr;
        QString m_routerAddr;
        QString m_maskAddr;
        bool m_enableDHCP;
        QString autoCmd = "nmcli con mod 'Wired connection 1' ipv4.method auto";
        QString staticCmd = "nmcli con mod 'Wired connection 1' ipv4.method manual";
        QString modCmd = "nmcli con mod 'Wired connection 1' ipv4.gateway ";
        QString upCon = "nmcli con up 'Wired connection 1'";

};
