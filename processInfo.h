#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <string>
#include <vector>

using namespace std;

class processInfo {
private:
    int pid;
    string Name;
    string Umask;
    string State;
    string PPid;
public:
    int getPid();
    string getName();
    string getUmask();
    string getState();
    string getPPid();

    void setPid(int pid);
    void setName(string Name);
    void setUmask(string Umask);
    void setState(string State);
    void setPPid(string PPid);

};

vector<processInfo> getVectorOfProcesses();


#endif // PROCESSINFO_H
