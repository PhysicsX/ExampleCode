#include <QObject>
#include <QProcess>
#include <QDebug>

#include "wifiConf.h"

WifiConf::WifiConf(): QObject()
{
    qDebug()<<"wifi conf is called";
    QProcess process;
    QString p_stdout;
    QString p_stderr;

    process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
    if(!process.waitForFinished())
        qDebug()<<"can not get hotspot name";
    p_stdout = process.readAllStandardOutput();
    qDebug()<<p_stdout;
    QString hotspot = "Hotspot";
    if(p_stdout.contains(hotspot, Qt::CaseInsensitive))
    {
        qDebug()<<"hotspot is active";
        enableHot = true;

    }
    else
    {
        qDebug()<<"station is active";

        process.start("bash", QStringList()<<"-c"<<"nmcli -f SSID device wifi");
        if(!process.waitForFinished())
            qDebug()<<"can not ssid list";
        p_stdout = process.readAllStandardOutput();
        qDebug()<<p_stdout;
        // QString str = "madam_curie\nhouse\noffice\noffice2";

        QStringList tmp = p_stdout.split("\n");
        for(int i = 0 ; i < tmp.size(); i++)
        {
            int truncateAt = tmp[i].size();
            int j = truncateAt-1;
            for(; j >= 0; j--)
            {
                if(tmp[i][j] != ' ')
                {
                    break;
                }
            }
            tmp[i].truncate(j+1);
        }
        for(int i = 0; i < tmp.size(); i++)
        {
            qDebug()<<tmp[i];
        }

        tmp.removeFirst(); // first is dummy SSID
        tmp.removeLast(); // last char
        //ssidNames = tmp;
        setSsidNames(tmp);

        enableHot = false;


    }
}

//setter functions

void WifiConf::setEnableHot(const bool flag)
{
    enableHot = flag;
    emit enableHotChanged();
}

void WifiConf::setSsidNames(const QStringList list)
{
    ssidNames = list;
    emit ssidNamesChanged();
}

void WifiConf::setHotSpotPassword(const QString pass)
{
    hotSpotPassword = pass;
    emit hotSpotPasswordChanged();
}

void WifiConf::setHotSpotSsid(const QString ssid)
{
    hotSpotSsid = ssid;
    emit hotSpotSsidChanged();
}

void WifiConf::setStationPassword(const QString pass)
{
    stationPassword = pass;
    emit stationPasswordChanged();
}

void WifiConf::setStationSsid(const QString ssid)
{
    stationSsid = ssid;
    emit stationSsidChanged();
}

//getter functions

bool WifiConf::getEnableHot() const
{
    return enableHot;
}

QStringList WifiConf::getSsidNames() const
{
    return ssidNames;
}

QString WifiConf::getHotSpotPassword() const
{
    return hotSpotPassword;
}

QString WifiConf::getHotSpotSsid() const
{
    return hotSpotSsid;
}

QString WifiConf::getStationPassword() const
{
    return stationPassword;
}

QString WifiConf::getStationSsid() const
{
    return stationSsid;
}

void WifiConf::updateHotspot(QString name, QString pass)
{
    qDebug()<<"hotspot name "<<name<<" pass "<<pass;
}


void WifiConf::connectToNetwork(QString name, QString pass)
{
    qDebug()<<"connect name "<<name<<" pass "<<pass;
    qDebug()<<name.length();
    QProcess process;
    QString p_stdout;
    process.start("bash", QStringList()<<"-c"<<"nmcli d wifi connect '"+name+"' password '"+pass+"'");
    if(!process.waitForFinished())
        qDebug()<<"can not connect "+name;
    p_stdout = process.readAllStandardOutput();
    qDebug()<<p_stdout;
}

void WifiConf::reScan()
{
    qDebug()<<"reScan network";
    QProcess process;
    QString p_stdout;
    process.start("bash", QStringList()<<"-c"<<"nmcli -f SSID device wifi");
    if(!process.waitForFinished())
        qDebug()<<"can not ssid list";
    p_stdout = process.readAllStandardOutput();
    qDebug()<<p_stdout;
    // QString str = "madam_curie\nhouse\noffice\noffice2";

    QStringList tmp = p_stdout.split("\n");
    tmp.removeFirst(); // first is dummy SSID
    tmp.removeLast(); // last char
    setSsidNames(tmp);
}

