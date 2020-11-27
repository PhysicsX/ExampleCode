#include <QObject>
#include <QDebug>
#include <QProcess>
#include "networkManager.h"
#include <thread>

NetworkManager::NetworkManager(): QObject()
{
    QProcess process;

    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  -w ipv4.method");
    process.waitForFinished();
    QString p_stdout = process.readAllStandardOutput();
    QString p_stderr = process.readAllStandardError();
    //qDebug()<<p_stdout;
    int lastSlash = p_stdout.lastIndexOf('\n');
    int prevSpace = p_stdout.lastIndexOf(' ');
    QString out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    //qDebug()<<out;
    if(out.contains("\n"))
        out = "";

    if(out == "manual")
    setEnableDHCP(true);
    else if(out == "auto")
    setEnableDHCP(false);

//    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  ipv4.address");
//    process.waitForFinished();
//    p_stdout = process.readAllStandardOutput();
//     p_stderr = process.readAllStandardError();
//    //qDebug()<<p_stdout;
//    //qDebug()<<p_stderr;
//    lastSlash = p_stdout.lastIndexOf('/');
//    prevSpace = p_stdout.lastIndexOf(' ');
//    out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
//    //qDebug()<<out;
//    if(out.contains("\n"))
//        out = "";

    process.start("bash", QStringList()<<"-c"<<"nmcli -g ip4.address connection show 'Wired connection 1'");
    process.waitForFinished();
    p_stdout = process.readAllStandardOutput();
    p_stderr = process.readAllStandardError();
    //qDebug()<<p_stdout;
    //qDebug()<<p_stderr;
    lastSlash = p_stdout.lastIndexOf('/');
    //prevSpace = p_stdout.lastIndexOf(' ');
    out = p_stdout.mid(0, lastSlash);
    //qDebug()<<out;
    if(out.contains("\n"))
        out = "";

    QString ip = out;
    setIpAddr(ip);

    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  -w routers");
    process.waitForFinished();
     p_stdout = process.readAllStandardOutput();
     p_stderr = process.readAllStandardError();
    //qDebug()<<p_stdout;
    lastSlash = p_stdout.lastIndexOf('\n');
    prevSpace = p_stdout.lastIndexOf(' ');
    out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    //qDebug()<<out;
    if(out.contains("\n"))
        out = "";

    setRouterAddr(out);

    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  -w subnet_mask");
    process.waitForFinished();
    p_stdout = process.readAllStandardOutput();
    p_stderr = process.readAllStandardError();
    //qDebug()<<p_stdout;
    lastSlash = p_stdout.lastIndexOf('\n');
    prevSpace = p_stdout.lastIndexOf(' ');
    out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    //qDebug()<<out;
    if(out.contains("\n"))
        out = "";

    setMaskAddr(out);


    qDebug()<<m_ipAddr;
    //m_enableDHCP = false;
    //emit enableDHCPChanged();
    //setDHCP();


    //for wifi configuration
    process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
    if(!process.waitForFinished())
        qDebug()<<"can not get hotspot name";
    p_stdout = process.readAllStandardOutput();
    qDebug()<<p_stdout;
    QString hotspot = "Hotspot";
    if(p_stdout.contains(hotspot, Qt::CaseInsensitive))
    {
        qDebug()<<"hotspot enabled";
        setEnableAP(false);
        setWlanMaskAddr("");
        setWlanRouterAddr("");
    }
    else
    {
        qDebug()<<"station enabled";
        setEnableAP(true);

        QString cmd = "nmcli -g ip4.gateway device show wlan0";
        process.start("bash", QStringList()<<"-c"<<cmd);
        process.waitForFinished();
        p_stdout = process.readAllStandardOutput();
        qDebug()<<"wif ip addr " + p_stdout;

        lastSlash = p_stdout.lastIndexOf("\n");
        //prevSpace = p_stdout.lastIndexOf(' ');
        out = p_stdout.mid(0, lastSlash);
        if(out.contains("\n"))
            out = "";

        setWlanRouterAddr(out);
        setWlanRouterAddr("");
    }
    QString cmd = "nmcli -g ip4.address device show wlan0";
    process.start("bash", QStringList()<<"-c"<<cmd);
    process.waitForFinished();
    p_stdout = process.readAllStandardOutput();
    qDebug()<<"wif ip addr " + p_stdout;

    lastSlash = p_stdout.lastIndexOf('/');
    //prevSpace = p_stdout.lastIndexOf(' ');
    out = p_stdout.mid(0, lastSlash);
    if(out.contains("\n"))
        out = "";

    QString wIp = out;
    setWlanIpAddr(wIp);

}

bool NetworkManager::setIp()
{
    qDebug()<<"Ip is set";
    return true;
}

void NetworkManager::setStaticConf(QString ip, QString mask, QString gateway)
{

}

void NetworkManager::applyNetwork(bool tabBar, bool conTab)
{
    //qDebug()<<"applyNetwork is called";
    //qDebug()<<tabBar<<" "<<conTab;
    if(conTab == 0)
    {
        if(tabBar == 0)
        {
            //qDebug()<<"Wired DHCP settings";
            setDHCP();
        }
        else
        {
            //qDebug()<<"Wired Static settings";
            setStatic();
        }

    }
    else if(conTab == 1)
    {

        if(tabBar == 0)
        {
            //qDebug()<<"Wifi AP settings";

            QProcess process;

            process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
            if(!process.waitForFinished())
                qDebug()<<"can not get hotspot name";
            QString p_stdout = process.readAllStandardOutput();
            qDebug()<<"hsda"<<p_stdout;

            int lastSlash = p_stdout.lastIndexOf("\n");
            //prevSpace = p_stdout.lastIndexOf(' ');
            QString out = p_stdout.mid(0, lastSlash);
            if(out.contains("\n"))
                out = "";
            QString cmd = "nmcli connection delete id "+out;
            process.start("bash", QStringList()<<"-c"<<cmd);
            if(!process.waitForFinished())
                qDebug()<<"wifi can not deleted, check wifi hardware is exist";

            process.start("bash", QStringList()<<"-c"<<"nmcli r wifi off"); // enable wifi
            if(!process.waitForFinished())
                qDebug()<<"wifi can not off, check wifi hardware is exist";


            process.start("bash", QStringList()<<"-c"<<"nmcli r wifi on"); // enable wifi
            if(!process.waitForFinished())
                qDebug()<<"wifi can not started, check wifi hardware is exist";


            std::thread t([this](){

                std::this_thread::sleep_for(std::chrono::milliseconds(5000));

                QProcess process;
                process.start("bash", QStringList()<<"-c"<<"nmcli dev wifi hotspot ifname wlan0 ssid EPILOG_AP password 'epilog2020'");
                if(process.waitForFinished())
                    qDebug()<<"Hotspot is created";
                else
                    qDebug()<<"Hotspot can not be created";


                process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
                if(!process.waitForFinished())
                    qDebug()<<"can not get hotspot name";
                QString p_stdout = process.readAllStandardOutput();
                qDebug()<<p_stdout;
                QString hotspot = "Hotspot";
                if(p_stdout.contains(hotspot, Qt::CaseInsensitive))
                {
                    QString cmd = "nmcli con up"+hotspot;
                    process.start("bash", QStringList()<<"-c"<<cmd);
                    if(!process.waitForFinished())
                        qDebug()<<"Hotspot can not bring up";
                }
                else
                {
                    qDebug()<<"Hotspot name can not find";
                }

                QString cmd = "nmcli -g ip4.address device show wlan0";
                process.start("bash", QStringList()<<"-c"<<cmd);
                process.waitForFinished();
                p_stdout = process.readAllStandardOutput();
                //qDebug()<<"wif ip addr " + p_stdout;

                int lastSlash = p_stdout.lastIndexOf('/');
                //prevSpace = p_stdout.lastIndexOf(' ');
                QString out = p_stdout.mid(0, lastSlash);
                if(out.contains("\n"))
                    out = "";

                QString wIp = out;
                setWlanIpAddr(wIp);
                setWlanMaskAddr("");
                setWlanRouterAddr("");

            });
            t.detach();


//            QTimer::singleShot(2000,[&]()
//            {
//                //qDebug()<<"timer single";
//                QProcess process;
//                process.start("bash", QStringList()<<"-c"<<"nmcli dev wifi hotspot ifname wlan0 ssid EPILOG_AP password 'epilog2020'");
//                if(process.waitForFinished())
//                    qDebug()<<"Hotspot is created";
//                else
//                    qDebug()<<"Hotspot can not be created";


//                process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
//                if(!process.waitForFinished())
//                    qDebug()<<"can not get hotspot name";
//                QString p_stdout = process.readAllStandardOutput();
//                qDebug()<<p_stdout;
//                QString hotspot = "Hotspot";
//                if(p_stdout.contains(hotspot, Qt::CaseInsensitive))
//                {
//                    QString cmd = "nmcli con up"+hotspot;
//                    process.start("bash", QStringList()<<"-c"<<cmd);
//                    if(!process.waitForFinished())
//                        qDebug()<<"Hotspot can not bring up";
//                }
//                else
//                {
//                    qDebug()<<"Hotspot name can not find";
//                }

//                QString cmd = "nmcli -g ip4.address device show wlan0";
//                process.start("bash", QStringList()<<"-c"<<cmd);
//                process.waitForFinished();
//                p_stdout = process.readAllStandardOutput();
//                qDebug()<<"wif ip addr " + p_stdout;

//                int lastSlash = p_stdout.lastIndexOf('/');
//                //prevSpace = p_stdout.lastIndexOf(' ');
//                QString out = p_stdout.mid(0, lastSlash);
//                if(out.contains("\n"))
//                    out = "";

//                QString wIp = out;
//                setWlanIpAddr(wIp);
//                setWlanMaskAddr("");
//                setWlanRouterAddr("");
//            });
        }
        else
        {
            //qDebug()<<"Wifi Station settings";

            QProcess process;

            process.start("bash", QStringList()<<"-c"<<"nmcli -g general.connection device show wlan0"); // get connection name (id)
            if(!process.waitForFinished())
                qDebug()<<"can not get hotspot name";
            QString p_stdout = process.readAllStandardOutput();
            qDebug()<<p_stdout;

            int lastSlash = p_stdout.lastIndexOf("\n");
            //prevSpace = p_stdout.lastIndexOf(' ');
            QString out = p_stdout.mid(0, lastSlash);
            if(out.contains("\n"))
                out = "";
            QString cmd = "nmcli connection delete id "+out;
            process.start("bash", QStringList()<<"-c"<<cmd);
            if(!process.waitForFinished())
                qDebug()<<"wifi can not deleted, check wifi hardware is exist";

            process.start("bash", QStringList()<<"-c"<<"nmcli r wifi off"); // enable wifi
            if(!process.waitForFinished())
                qDebug()<<"wifi can not off, check wifi hardware is exist";


            process.start("bash", QStringList()<<"-c"<<"nmcli r wifi on"); // enable wifi
            if(!process.waitForFinished())
                qDebug()<<"wifi can not started, check wifi hardware is exist";

        }

    }
    else
    {
        qDebug()<<"wrong conTab parameter";
    }
}

void NetworkManager::setIpAddr(const QString &ip)
{
    //qDebug()<<"setIpAddr";
    m_ipAddr = ip;
    emit ipAddrChanged();
}

void NetworkManager::setEnableDHCP(const bool flag)
{
    //qDebug()<<"setEnableDHCP";
    m_enableDHCP = flag;
    emit enableDHCPChanged();
}

void NetworkManager::setMaskAddr(const QString &mask)
{
    m_maskAddr = mask;
    emit maskAddrChanged();
}


void NetworkManager::setRouterAddr(const QString &routerAddr)
{
    m_routerAddr = routerAddr;
    emit routerAddrChanged();
}

void NetworkManager::setWlanIpAddr(const QString &wIp)
{
    m_WipAddr = wIp;
    emit wlanIpAddrChanged();
}

void NetworkManager::setWlanRouterAddr(const QString &wRouter)
{
    m_WmaskAddr = wRouter;
    emit wlanRouterAddrChanged();
}

void NetworkManager::setWlanMaskAddr(const QString &wMask)
{
    m_WrouterAddr = wMask;
    emit wlanMaskAddrChanged();
}

void NetworkManager::setEnableAP(const bool wFlag)
{
    m_enableAP = wFlag;
    emit enableAPChanged();
}

QString NetworkManager::getIpAddr() const
{
    return m_ipAddr;
}

QString NetworkManager::getRouterAddr() const
{
    return m_routerAddr;
}

QString NetworkManager::getMaskAddr() const
{
    return m_maskAddr;
}

bool NetworkManager::getEnableDHCP() const
{
    return m_enableDHCP;
}

QString NetworkManager::getWlanIpAddr() const
{
    return m_WipAddr;
}

QString NetworkManager::getWlanRouterAddr() const
{
    return m_WrouterAddr;
}

QString NetworkManager::getWlanMaskAddr() const
{
    return m_WmaskAddr;
}

bool NetworkManager::getEnableAP() const
{
    return m_enableAP;
}

bool NetworkManager::setDHCP()
{
    QProcess process;
    bool result = true;
    // set Auto for wired
    process.start("bash", QStringList()<<"-c"<<autoCmd);
    result = process.waitForFinished();

    if(!result)
    {
        qDebug()<<"setDHPC failed "<<result;
        return result;
    }

    process.start("bash", QStringList()<<"-c"<<"nmcli -g ip4.address connection show 'Wired connection 1'");
    process.waitForFinished();
    QString p_stdout = process.readAllStandardOutput();
    QString p_stderr = process.readAllStandardError();
    //qDebug()<<p_stdout;
    //qDebug()<<p_stderr;
    int lastSlash = p_stdout.lastIndexOf('/');
    int prevSpace = p_stdout.lastIndexOf(' ');
    //qDebug()<<out;
    QString out = p_stdout.mid(0, lastSlash);
    if(out.contains("\n"))
        out = "";

    QString ip = out;
    setIpAddr(ip);

    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  -w routers");
    process.waitForFinished();
     p_stdout = process.readAllStandardOutput();
     p_stderr = process.readAllStandardError();
    qDebug()<<p_stdout;
    lastSlash = p_stdout.lastIndexOf('\n');
    prevSpace = p_stdout.lastIndexOf(' ');
    out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    qDebug()<<out;
    if(out.contains("\n"))
        out = "";

    setRouterAddr(out);

    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  -w subnet_mask");
    process.waitForFinished();
     p_stdout = process.readAllStandardOutput();
     p_stderr = process.readAllStandardError();
    qDebug()<<p_stdout;
    lastSlash = p_stdout.lastIndexOf('\n');
    prevSpace = p_stdout.lastIndexOf(' ');
    out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    qDebug()<<out;
    if(out.contains("\n"))
        out = "";

    setMaskAddr(out);

    process.start("bash", QStringList()<<"-c"<<upCon);
    process.waitForFinished();

    if(!result)
    {
        qDebug()<<"setDHPC upCon failed "<<result;
        return result;
    }

    return result;
}

bool NetworkManager::setStatic()
{
    bool result = false;

    QProcess process;
    //qDebug()<<"SetStatic function is called";
    // set Manual for wired
    process.start("bash", QStringList()<<"-c"<<staticCmd);
    result = process.waitForFinished();

    if(!result)
    {
        qDebug()<<"setStatıc failed "<<result;
        return result;
    }

    QString ip = m_ipAddr;
    qDebug()<<ip;
    QString cmd = "nmcli con mod 'Wired connection 1' ipv4.addresses "+ip+"/24";
    process.start("bash", QStringList()<<"-c"<<cmd);
    process.waitForFinished();
    QString p_stdout = process.readAllStandardOutput();
    QString p_stderr = process.readAllStandardError();
    qDebug()<<p_stdout;
    qDebug()<<p_stderr;

    QString gateway = m_routerAddr;
    //qDebug()<<gateway;
    cmd = "nmcli con mod 'Wired connection 1' ipv4.gateway "+gateway;
    process.start("bash", QStringList()<<"-c"<<cmd);
    process.waitForFinished();
    p_stdout = process.readAllStandardOutput();
    p_stderr = process.readAllStandardError();
    //qDebug()<<p_stdout;
    //qDebug()<<p_stderr;

//    QString mask = m_maskAddr;
//    process.start("bash", QStringList()<<"-c"<<"nmcli con mod 'Wired connection 1' ipv4.method "+mask);
//    process.waitForFinished();
//    p_stdout = process.readAllStandardOutput();
//    p_stderr = process.readAllStandardError();
//    qDebug()<<p_stdout;
//    qDebug()<<p_stderr;

    process.start("bash", QStringList()<<"-c"<<upCon);
    process.waitForFinished();

    if(!result)
    {
        qDebug()<<"setDHPC upCon failed "<<result;
        return result;
    }

    return result;
}
