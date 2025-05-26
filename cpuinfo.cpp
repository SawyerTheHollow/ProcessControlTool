#include "cpuinfo.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <QDebug>

using namespace std;

int cpuInfo::getuser(){
    return user;
}

int cpuInfo::getnice(){
    return nice;
}

int cpuInfo::getsystem(){
    return system;
}

int cpuInfo::getidle(){
    return idle;
}

int cpuInfo::getiowait(){
    return iowait;
}

int cpuInfo::getirq(){
    return irq;
}

int cpuInfo::getsoftirq(){
    return softirq;
}

int cpuInfo::getsteal(){
    return steal;
}

int cpuInfo::getguest(){
    return guest;
}

int cpuInfo::getguest_nice(){
    return guest_nice;
}

int cpuInfo::gettotal(){
    return total;
}

void cpuInfo::setuser(int user){
    this->user = user;
}

void cpuInfo::setnice(int nice){
    this->nice = nice;
}

void cpuInfo::setsystem(int system){
    this->system = system;
}

void cpuInfo::setidle(int idle){
    this->idle = idle;
}

void cpuInfo::setiowait(int iowait){
    this->iowait = iowait;
}

void cpuInfo::setirq(int irq){
    this->irq = irq;
}

void cpuInfo::setsoftirq(int softirq){
    this->softirq = softirq;
}

void cpuInfo::setsteal(int steal){
    this->steal = steal;
}

void cpuInfo::setguest(int guest){
    this->guest = guest;
}

void cpuInfo::setguest_nice(int guest_nice){
    this->guest_nice = guest_nice;
}

cpuInfo cpuInfo::getCpuInfo(){
    string statusFile = string("/proc/stat");
    ifstream statusFileStream(statusFile);
    cpuInfo cpu;

    if (statusFileStream.is_open()) {

        string line;
        while (getline(statusFileStream, line)) {

            if (line.compare(0, 4, "cpu ") == 0) {

                istringstream cpuLineStringStream(line);
                string cpuLineField;
                string cpuLabel;

                cpuLineStringStream >> cpuLabel;
                cpuLineStringStream >> cpu.user >> cpu.nice >> cpu.system >> cpu.idle >> cpu.iowait >> cpu.irq >> cpu.softirq >> cpu.steal >> cpu.guest >> cpu.guest_nice;
                cpu.total = cpu.user + cpu.nice + cpu.system + cpu.idle + cpu.iowait + cpu.irq + cpu.softirq + cpu.steal + cpu.guest + cpu.guest_nice;
            }
        }
    }
    return cpu;
}
