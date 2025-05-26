#ifndef CPUINFO_H
#define CPUINFO_H

class cpuInfo
{
private:
    int user;
    int nice;
    int system;
    int idle;
    int iowait;
    int irq;
    int softirq;
    int steal;
    int guest;
    int guest_nice;

    int total;
public:
    int getuser();
    int getnice();
    int getsystem();
    int getidle();
    int getiowait();
    int getirq();
    int getsoftirq();
    int getsteal();
    int getguest();
    int getguest_nice();
    int gettotal();

    void setuser(int user);
    void setnice(int nice);
    void setsystem(int system);
    void setidle(int idle);
    void setiowait(int iowait);
    void setirq(int irq);
    void setsoftirq(int softirq);
    void setsteal(int steal);
    void setguest(int guest);
    void setguest_nice(int guest_nice);

    static cpuInfo getCpuInfo();
};

#endif // CPUINFO_H
