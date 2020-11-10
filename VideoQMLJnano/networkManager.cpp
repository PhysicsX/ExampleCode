#include <QObject>
#include <QDebug>
#include <QProcess>
#include "networkManager.h"


NetworkManager::NetworkManager(): QObject()
{
    qDebug()<<"BEginninnnngngngngn";
    QProcess process;

    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  -w ipv4.method");
    process.waitForFinished();
    QString p_stdout = process.readAllStandardOutput();
    QString p_stderr = process.readAllStandardError();
    qDebug()<<p_stdout;
    int lastSlash = p_stdout.lastIndexOf('\n');
    int prevSpace = p_stdout.lastIndexOf(' ');
    QString out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    qDebug()<<out;
    if(out.contains("\n"))
        out = "";

    if(out == "manual")
    setEnableDHCP(true);
    else if(out == "auto")
    setEnableDHCP(false);

    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  ipv4.address");
    process.waitForFinished();
    p_stdout = process.readAllStandardOutput();
     p_stderr = process.readAllStandardError();
    //qDebug()<<p_stdout;
    //qDebug()<<p_stderr;
    lastSlash = p_stdout.lastIndexOf('/');
    prevSpace = p_stdout.lastIndexOf(' ');
    out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    //qDebug()<<out;
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


    qDebug()<<m_ipAddr;
    //m_enableDHCP = false;
    //emit enableDHCPChanged();
    //setDHCP();
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
    qDebug()<<"here here";
    qDebug()<<tabBar<<" "<<conTab;
    if(conTab == 0)
    {
        if(tabBar == 0)
        {
            qDebug()<<"Wired DHCP settings";
            setDHCP();
        }
        else
        {
            qDebug()<<"Wired Static settings";
            setStatic();
        }

    }
}

void NetworkManager::setIpAddr(const QString &ip)
{
    qDebug()<<"setIpAddr";
    m_ipAddr = ip;
    emit ipAddrChanged();
}

void NetworkManager::setEnableDHCP(const bool flag)
{
    qDebug()<<"setEnableDHCP";
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



    process.start("bash", QStringList()<<"-c"<<"nmcli connection show 'Wired connection 1' | grep  ipv4.address");
    process.waitForFinished();
    QString p_stdout = process.readAllStandardOutput();
    QString p_stderr = process.readAllStandardError();
    qDebug()<<p_stdout;
    //qDebug()<<p_stderr;
    int lastSlash = p_stdout.lastIndexOf('/');
    int prevSpace = p_stdout.lastIndexOf(' ');
    QString out = p_stdout.mid(prevSpace+1, lastSlash - prevSpace-1);
    qDebug()<<out;
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
    qDebug()<<"SetStatic function is called";
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
    qDebug()<<gateway;
    cmd = "nmcli con mod 'Wired connection 1' ipv4.gateway "+gateway;
    process.start("bash", QStringList()<<"-c"<<cmd);
    process.waitForFinished();
    p_stdout = process.readAllStandardOutput();
    p_stderr = process.readAllStandardError();
    qDebug()<<p_stdout;
    qDebug()<<p_stderr;

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
