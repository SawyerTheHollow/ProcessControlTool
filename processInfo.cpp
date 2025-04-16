#include "dirent.h"
#include "fstream"
#include <string>
#include <vector>

#include "processInfo.h"

using namespace std;

int processInfo::getPid(){
    return pid;
}

string processInfo::getName(){
    return Name;
}

string processInfo::getState(){
    return State;
}

string processInfo::getUmask(){
    return Umask;
}

string processInfo::getPPid(){
    return PPid;
}

void processInfo::setPid(int pid){
    this->pid = pid;
}

void processInfo::setName(string Name){
    this->Name = Name;
}

void processInfo::setUmask(string Umask){
    this->Umask = Umask;
}

void processInfo::setState(string State){
    this->State = State;
}

void processInfo::setPPid(string PPid){
    this->PPid = PPid;
}

vector<processInfo> getVectorOfProcesses(){

    vector<processInfo> processes;
    DIR* procDirectory = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(procDirectory)) != nullptr) {

        // Проверяем, является ли название папки числом
        if (isdigit(entry->d_name[0])) {

            // Преобразуем название папки в PID
            int pid = stoi(entry->d_name);

            // Формирование строки с путём до папки со статусом для PIDа
            string statusFile = string("/proc/") + entry->d_name + "/status";

            ifstream file(statusFile);
            if (file.is_open()) {
                processInfo process;
                process.setPid(pid);

                string line;
                while (getline(file, line)) {

                    // Извлекаем Name процесса
                    if (line.find("Name:") == 0) {
                        process.setName(line.substr(6));
                    }

                    // Извлекаем Umask процесса
                    else if (line.find("Umask:") == 0) {
                        process.setUmask(line.substr(7));
                    }

                    // Извлекаем State процесса
                    else if (line.find("State:") == 0) {
                        process.setState(line.substr(7));
                    }

                    // Извлекаем PPID процесса
                    else if (line.find("PPid:") == 0) {
                        process.setPPid(line.substr(6));
                    }

                }
                processes.push_back(process);
            }
        }
    }
   closedir(procDirectory);
    return processes;
}
