#include "dirent.h"
#include "fstream"
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <QDebug>

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

string processInfo::getTgid(){
    return Tgid;
}

string processInfo::getNgid(){
    return Ngid;
}

string processInfo::getTracerPid(){
    return TracerPid;
}

string processInfo::getUid(){
    return Uid;
}

string processInfo::getGid(){
    return Gid;
}

string processInfo::getFDSize(){
    return FDSize;
}

string processInfo::getGroups(){
    return Groups;
}

string processInfo::getNStgid(){
    return NStgid;
}

string processInfo::getNSpid(){
    return NSpid;
}

string processInfo::getNSpgid(){
    return NSpgid;
}

string processInfo::getNSsid(){
    return NSsid;
}

string processInfo::getKthread(){
    return Kthread;
}

string processInfo::getVmPeak(){
    return VmPeak;
}

string processInfo::getVmSize(){
    return VmSize;
}

string processInfo::getVmLck(){
    return VmLck;
}

string processInfo::getVmPin(){
    return VmPin;
}

string processInfo::getVmHWM(){
    return VmHWM;
}

string processInfo::getVmRSS(){
    return VmRSS;
}

string processInfo::getRssAnon(){
    return RssAnon;
}

string processInfo::getRssFile(){
    return RssFile;
}

string processInfo::getRssShmem(){
    return RssShmem;
}

string processInfo::getVmData(){
    return VmData;
}

string processInfo::getVmStk(){
    return VmStk;
}

string processInfo::getVmExe(){
    return VmExe;
}

string processInfo::getVmLib(){
    return VmLib;
}

string processInfo::getVmPTE(){
    return VmPTE;
}

string processInfo::getVmSwap(){
    return VmSwap;
}

string processInfo::getHugetlbPages(){
    return HugetlbPages;
}

string processInfo::getCoreDumping(){
    return CoreDumping;
}

string processInfo::getTHP_enabled(){
    return THP_enabled;
}

string processInfo::getuntag_mask(){
    return untag_mask;
}

string processInfo::getThreads(){
    return Threads;
}

string processInfo::getSigQ(){
    return SigQ;
}

string processInfo::getSigPnd(){
    return SigPnd;
}

string processInfo::getShdPnd(){
    return ShdPnd;
}

string processInfo::getSigBlk(){
    return SigBlk;
}

string processInfo::getSigIgn(){
    return SigIgn;
}

string processInfo::getSigCgt(){
    return SigCgt;
}

string processInfo::getCapInh(){
    return CapInh;
}

string processInfo::getCapPrm(){
    return CapPrm;
}

string processInfo::getCapEff(){
    return CapEff;
}

string processInfo::getCapBnd(){
    return CapBnd;
}

string processInfo::getCapAmb(){
    return CapAmb;
}

string processInfo::getNoNewPrivs(){
    return NoNewPrivs;
}

string processInfo::getSeccomp(){
    return Seccomp;
}

string processInfo::getSeccomp_filters(){
    return Seccomp_filters;
}

string processInfo::getSpeculation_Store_Bypass(){
    return Speculation_Store_Bypass;
}

string processInfo::getSpeculationIndirectBranch(){
    return SpeculationIndirectBranch;
}

string processInfo::getCpus_allowed(){
    return Cpus_allowed;
}

string processInfo::getCpus_allowed_list(){
    return Cpus_allowed_list;
}

string processInfo::getMems_allowed(){
    return Mems_allowed;
}

string processInfo::getMems_allowed_list(){
    return Mems_allowed_list;
}

string processInfo::getvoluntary_ctxt_switches(){
    return voluntary_ctxt_switches;
}

string processInfo::getnonvoluntary_ctxt_switches(){
    return nonvoluntary_ctxt_switches;
}

string processInfo::getx86_Thread_features(){
    return x86_Thread_features;
}

string processInfo::getx86_Thread_features_locked(){
    return x86_Thread_features_locked;
}

string processInfo::getpgrp(){
    return pgrp;
}

string processInfo::getsession(){
    return session;
}

string processInfo::gettty_nr(){
    return tty_nr;
}

string processInfo::gettpgid(){
    return tpgid;
}

string processInfo::getflags(){
    return flags;
}

string processInfo::getminflt(){
    return minflt;
}

string processInfo::getcminflt(){
    return cminflt;
}

string processInfo::getmajflt(){
    return majflt;
}

string processInfo::getcmajflt(){
    return cmajflt;
}

string processInfo::getutime(){
    return utime;
}

string processInfo::getstime(){
    return stime;
}

string processInfo::getcutime(){
    return cutime;
}

string processInfo::getcstime(){
    return cstime;
}

string processInfo::getpriority(){
    return priority;
}

string processInfo::getnice(){
    return nice;
}

string processInfo::getnum_threads(){
    return num_threads;
}

string processInfo::getitrealvalue(){
    return itrealvalue;
}

string processInfo::getstarttime(){
    return starttime;
}

string processInfo::getvsize(){
    return vsize;
}

string processInfo::getrss(){
    return rss;
}

string processInfo::getrsslim(){
    return rsslim;
}

string processInfo::getstartcode(){
    return startcode;
}

string processInfo::getendcode(){
    return endcode;
}

string processInfo::getstartstack(){
    return startstack;
}

string processInfo::getkstkesp(){
    return kstkesp;
}

string processInfo::getkstkeip(){
    return kstkeip;
}

string processInfo::getsignal(){
    return signal;
}

string processInfo::getblocked(){
    return blocked;
}

string processInfo::getsigignore(){
    return sigignore;
}

string processInfo::getsigcatch(){
    return sigcatch;
}

string processInfo::getwchan(){
    return wchan;
}

string processInfo::getnswap(){
    return nswap;
}

string processInfo::getcnswap(){
    return cnswap;
}

string processInfo::getexit_signal(){
    return exit_signal;
}

string processInfo::getprocessor(){
    return processor;
}

string processInfo::getrt_priority(){
    return rt_priority;
}

string processInfo::getpolicy(){
    return policy;
}

string processInfo::getdelayacct_blkio_ticks(){
    return delayacct_blkio_ticks;
}

string processInfo::getguest_time(){
    return guest_time;
}

string processInfo::getcguest_time(){
    return cguest_time;
}

string processInfo::getstart_data(){
    return start_data;
}

string processInfo::getend_data(){
    return end_data;
}

string processInfo::getstart_brk(){
    return start_brk;
}

string processInfo::getarg_start(){
    return arg_start;
}

string processInfo::getarg_end(){
    return arg_end;
}

string processInfo::getenv_start(){
    return env_start;
}

string processInfo::getenv_end(){
    return env_end;
}

string processInfo::getexit_code(){
    return exit_code;
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

void processInfo::setTgid(string Tgid){
    this->Tgid = Tgid;
}

void processInfo::setNgid(string Ngid){
    this->Ngid = Ngid;
}

void processInfo::setTracerPid(string TracerPid){
    this->TracerPid = TracerPid;
}

void processInfo::setUid(string Uid){
    this->Uid = Uid;
}

void processInfo::setGid(string Gid){
    this->Gid = Gid;
}

void processInfo::setFDSize(string FDSize){
    this->FDSize = FDSize;
}

void processInfo::setGroups(string Groups){
    this->Groups = Groups;
}

void processInfo::setNStgid(string NStgid){
    this->NStgid = NStgid;
}

void processInfo::setNSpid(string NSpid){
    this->NSpid = NSpid;
}

void processInfo::setNSpgid(string NSpgid){
    this->NSpgid = NSpgid;
}

void processInfo::setNSsid(string NSsid){
    this->NSsid = NSsid;
}

void processInfo::setKthread(string Kthread){
    this->Kthread = Kthread;
}

void processInfo::setVmPeak(string VmPeak){
    this->VmPeak = VmPeak;
}

void processInfo::setVmSize(string VmSize){
    this->VmSize = VmSize;
}

void processInfo::setVmLck(string VmLck){
    this->VmLck = VmLck;
}

void processInfo::setVmPin(string VmPin){
    this->VmPin = VmPin;
}

void processInfo::setVmHWM(string VmHWM){
    this->VmHWM = VmHWM;
}

void processInfo::setVmRSS(string VmRSS){
    this->VmRSS = VmRSS;
}

void processInfo::setRssAnon(string RssAnon){
    this->RssAnon = RssAnon;
}

void processInfo::setRssFile(string RssFile){
    this->RssFile = RssFile;
}

void processInfo::setRssShmem(string RssShmem){
    this->RssShmem = RssShmem;
}

void processInfo::setVmData(string VmData){
    this->VmData = VmData;
}

void processInfo::setVmStk(string VmStk){
    this->VmStk = VmStk;
}

void processInfo::setVmExe(string VmExe){
    this->VmExe = VmExe;
}

void processInfo::setVmLib(string VmLib){
    this->VmLib = VmLib;
}

void processInfo::setVmPTE(string VmPTE){
    this->VmPTE = VmPTE;
}

void processInfo::setVmSwap(string VmSwap){
    this->VmSwap = VmSwap;
}

void processInfo::setHugetlbPages(string HugetlbPages){
    this->HugetlbPages = HugetlbPages;
}

void processInfo::setCoreDumping(string CoreDumping){
    this->CoreDumping = CoreDumping;
}

void processInfo::setTHP_enabled(string THP_enabled){
    this->THP_enabled = THP_enabled;
}

void processInfo::setuntag_mask(string untag_mask){
    this->untag_mask = untag_mask;
}

void processInfo::setThreads(string Threads){
    this->Threads = Threads;
}

void processInfo::setSigQ(string SigQ){
    this->SigQ = SigQ;
}

void processInfo::setSigPnd(string SigPnd){
    this->SigPnd = SigPnd;
}

void processInfo::setShdPnd(string ShdPnd){
    this->ShdPnd = ShdPnd;
}

void processInfo::setSigBlk(string SigBlk){
    this->SigBlk = SigBlk;
}

void processInfo::setSigIgn(string SigIgn){
    this->SigIgn = SigIgn;
}

void processInfo::setSigCgt(string SigCgt){
    this->SigCgt = SigCgt;
}

void processInfo::setCapInh(string CapInh){
    this->CapInh = CapInh;
}

void processInfo::setCapPrm(string CapPrm){
    this->CapPrm = CapPrm;
}

void processInfo::setCapEff(string CapEff){
    this->CapEff = CapEff;
}

void processInfo::setCapBnd(string CapBnd){
    this->CapBnd = CapBnd;
}

void processInfo::setCapAmb(string CapAmb){
    this->CapAmb = CapAmb;
}

void processInfo::setNoNewPrivs(string NoNewPrivs){
    this->NoNewPrivs = NoNewPrivs;
}

void processInfo::setSeccomp(string Seccomp){
    this->Seccomp = Seccomp;
}

void processInfo::setSeccomp_filters(string Seccomp_filters){
    this->Seccomp_filters = Seccomp_filters;
}

void processInfo::setSpeculation_Store_Bypass(string Speculation_Store_Bypass){
    this->Speculation_Store_Bypass = Speculation_Store_Bypass;
}

void processInfo::setSpeculationIndirectBranch(string SpeculationIndirectBranch){
    this->SpeculationIndirectBranch = SpeculationIndirectBranch;
}

void processInfo::setCpus_allowed(string Cpus_allowed){
    this->Cpus_allowed = Cpus_allowed;
}

void processInfo::setCpus_allowed_list(string Cpus_allowed_list){
    this->Cpus_allowed_list = Cpus_allowed_list;
}

void processInfo::setMems_allowed(string Mems_allowed){
    this->Mems_allowed = Mems_allowed;
}
void processInfo::setMems_allowed_list(string Mems_allowed_list){
    this->Mems_allowed_list = Mems_allowed_list;
}

void processInfo::setvoluntary_ctxt_switches(string voluntary_ctxt_switches){
    this->voluntary_ctxt_switches = voluntary_ctxt_switches;
}

void processInfo::setnonvoluntary_ctxt_switches(string nonvoluntary_ctxt_switches){
    this->nonvoluntary_ctxt_switches = nonvoluntary_ctxt_switches;
}

void processInfo::setx86_Thread_features(string x86_Thread_features){
    this->x86_Thread_features = x86_Thread_features;
}

void processInfo::setx86_Thread_features_locked(string x86_Thread_features_locked){
    this->x86_Thread_features_locked = x86_Thread_features_locked;
}

void processInfo::setpgrp(string pgrp){
    this->pgrp = pgrp;
}

void processInfo::setsession(string session){
    this->session = session;
}

void processInfo::settty_nr(string tty_nr){
    this->tty_nr = tty_nr;
}

void processInfo::settpgid(string tpgid){
    this->tpgid = tpgid;
}

void processInfo::setflags(string flags){
    this->flags = flags;
}

void processInfo::setminflt(string minflt){
    this->minflt = minflt;
}

void processInfo::setcminflt(string cminflt){
    this->cminflt = cminflt;
}

void processInfo::setmajflt(string majflt){
    this->majflt = majflt;
}

void processInfo::setcmajflt(string cmajflt){
    this->cmajflt = cmajflt;
}

void processInfo::setutime(string utime){
    this->utime = utime;
}

void processInfo::setstime(string stime){
    this->stime = stime;
}

void processInfo::setcutime(string cutime){
    this->cutime = cutime;
}

void processInfo::setcstime(string cstime){
    this->cstime = cstime;
}


void processInfo::setpriority(string priority){
    this->priority = priority;
}

void processInfo::setnice(string nice){
    this->nice = nice;
}

void processInfo::setnum_threads(string num_threads){
    this->num_threads = num_threads;
}

void processInfo::setitrealvalue(string itrealvalue){
    this->itrealvalue = itrealvalue;
}

void processInfo::setstarttime(string starttime){
    this->starttime = starttime;
}

void processInfo::setvsize(string vsize){
    this->vsize = vsize;
}

void processInfo::setrss(string rss){
    this->rss = rss;
}

void processInfo::setrsslim(string rsslim){
    this->rsslim = rsslim;
}

void processInfo::setstartcode(string startcode){
    this->startcode = startcode;
}

void processInfo::setendcode(string endcode){
    this->endcode = endcode;
}

void processInfo::setstartstack(string startstack){
    this->startstack = startstack;
}

void processInfo::setkstkesp(string kstkesp){
    this->kstkesp = kstkesp;
}

void processInfo::setkstkeip(string kstkeip){
    this->kstkeip = kstkeip;
}

void processInfo::setsignal(string signal){
    this->signal = signal;
}

void processInfo::setblocked(string blocked){
    this->blocked = blocked;
}

void processInfo::setsigignore(string sigignore){
    this->sigignore = sigignore;
}

void processInfo::setsigcatch(string sigcatch){
    this->sigcatch = sigcatch;
}

void processInfo::setwchan(string wchan){
    this->wchan = wchan;
}

void processInfo::setnswap(string nswap){
    this->nswap = nswap;
}

void processInfo::setcnswap(string cnswap){
    this->cnswap = cnswap;
}

void processInfo::setexit_signal(string exit_signal){
    this->exit_signal = exit_signal;
}

void processInfo::setprocessor(string processor){
    this->processor = processor;
}

void processInfo::setrt_priority(string rt_priority){
    this->rt_priority = rt_priority;
}

void processInfo::setpolicy(string policy){
    this->policy = policy;
}

void processInfo::setdelayacct_blkio_ticks(string delayacct_blkio_ticks){
    this->delayacct_blkio_ticks = delayacct_blkio_ticks;
}

void processInfo::setguest_time(string guest_time){
    this->guest_time = guest_time;
}

void processInfo::setcguest_time(string cguest_time){
    this->cguest_time = cguest_time;
}

void processInfo::setstart_data(string start_data){
    this->start_data = start_data;
}

void processInfo::setend_data(string end_data){
    this->end_data = end_data;
}

void processInfo::setstart_brk(string start_brk){
    this->start_brk = start_brk;
}

void processInfo::setarg_start(string arg_start){
    this->arg_start = arg_start;
}

void processInfo::setarg_end(string arg_end){
    this->arg_end = arg_end;
}

void processInfo::setenv_start(string env_start){
    this->env_start = env_start;
}

void processInfo::setenv_end(string env_end){
    this->env_end = env_end;
}

void processInfo::setexit_code(string exit_code){
    this->exit_code = exit_code;
}

vector<processInfo> getVectorOfProcesses(){

    vector<processInfo> processes;
    DIR* procDirectory = opendir("/proc");
    struct dirent* entry;

    while ((entry = readdir(procDirectory)) != nullptr) {

        if (isdigit(entry->d_name[0])) {

            int pid = stoi(entry->d_name);

            string statusFile = string("/proc/") + entry->d_name + "/status";
            string statFile = string("/proc/") + entry->d_name + "/stat";

            ifstream statusFileStream(statusFile);
            ifstream statFileStream(statFile);

            vector<string> vectorOfStatFields;

            if (statusFileStream.is_open() && statFileStream.is_open()) {
                processInfo process;
                process.setPid(pid);

                string line;
                while (getline(statusFileStream, line)) {

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

                    // Извлекаем Tgid процесса
                    else if (line.find("Tgid:") == 0) {
                        process.setTgid(line.substr(6));
                    }

                    // Извлекаем Ngid процесса
                    else if (line.find("Ngid:") == 0) {
                        process.setNgid(line.substr(6));
                    }

                    // Извлекаем TracerPid процесса
                    else if (line.find("TracerPid:") == 0) {
                        process.setTracerPid(line.substr(11));
                    }

                    // Извлекаем Uid процесса
                    else if (line.find("Uid:") == 0) {
                        process.setUid(line.substr(5));
                    }

                    // Извлекаем Gid процесса
                    else if (line.find("Gid:") == 0) {
                        process.setGid(line.substr(5));
                    }

                    // Извлекаем FDSize процесса
                    else if (line.find("FDSize:") == 0) {
                        process.setFDSize(line.substr(8));
                    }

                    // Извлекаем Groups процесса
                    else if (line.find("Groups:") == 0) {
                        process.setGroups(line.substr(7));
                    }

                    // Извлекаем NStgid процесса
                    else if (line.find("NStgid:") == 0) {
                        process.setNStgid(line.substr(8));
                    }

                    // Извлекаем NSpid процесса
                    else if (line.find("NSpid:") == 0) {
                        process.setNSpid(line.substr(7));
                    }

                    // Извлекаем NSpgid процесса
                    else if (line.find("NSpgid:") == 0) {
                        process.setNSpgid(line.substr(8));
                    }

                    // Извлекаем NSsid процесса
                    else if (line.find("NSsid:") == 0) {
                        process.setNSsid(line.substr(6));
                    }

                    // Извлекаем Kthread процесса
                    else if (line.find("Kthread:") == 0) {
                        process.setKthread(line.substr(8));
                    }

                    // Извлекаем VmPeak процесса
                    else if (line.find("VmPeak:") == 0) {
                        process.setVmPeak(line.substr(7));
                    }

                    // Извлекаем VmSize процесса
                    else if (line.find("VmSize:") == 0) {
                        process.setVmSize(line.substr(7));
                    }

                    // Извлекаем VmLck процесса
                    else if (line.find("VmLck:") == 0) {
                        process.setVmLck(line.substr(6));
                    }

                    // Извлекаем VmPin процесса
                    else if (line.find("VmPin:") == 0) {
                        process.setVmPin(line.substr(6));
                    }

                    // Извлекаем VmHWM процесса
                    else if (line.find("VmHWM:") == 0) {
                        process.setVmHWM(line.substr(6));
                    }

                    // Извлекаем VmRSS процесса
                    else if (line.find("VmRSS:") == 0) {
                        process.setVmRSS(line.substr(6));
                    }

                    // Извлекаем RssAnon процесса
                    else if (line.find("RssAnon:") == 0) {
                        process.setRssAnon(line.substr(8));
                    }

                    // Извлекаем RssFile процесса
                    else if (line.find("RssFile:") == 0) {
                        process.setRssFile(line.substr(8));
                    }

                    // Извлекаем RssShmem процесса
                    else if (line.find("RssShmem:") == 0) {
                        process.setRssShmem(line.substr(9));
                    }

                    // Извлекаем VmData процесса
                    else if (line.find("VmData:") == 0) {
                        process.setVmData(line.substr(7));
                    }

                    // Извлекаем VmStk процесса
                    else if (line.find("VmStk:") == 0) {
                        process.setVmStk(line.substr(6));
                    }

                    // Извлекаем VmExe процесса
                    else if (line.find("VmExe:") == 0) {
                        process.setVmExe(line.substr(6));
                    }

                    // Извлекаем VmLib процесса
                    else if (line.find("VmLib:") == 0) {
                        process.setVmLib(line.substr(6));
                    }

                    // Извлекаем VmPTE процесса
                    else if (line.find("VmPTE:") == 0) {
                        process.setVmPTE(line.substr(6));
                    }

                    // Извлекаем VmSwap процесса
                    else if (line.find("VmSwap:") == 0) {
                        process.setVmSwap(line.substr(7));
                    }

                    // Извлекаем HugetlbPages процесса
                    else if (line.find("HugetlbPages:") == 0) {
                        process.setHugetlbPages(line.substr(13));
                    }

                    // Извлекаем CoreDumping процесса
                    else if (line.find("CoreDumping:") == 0) {
                        process.setCoreDumping(line.substr(12));
                    }

                    // Извлекаем THP_enabled процесса
                    else if (line.find("THP_enabled:") == 0) {
                        process.setTHP_enabled(line.substr(12));
                    }

                    // Извлекаем untag_mask процесса
                    else if (line.find("untag_mask:") == 0) {
                        process.setuntag_mask(line.substr(11));
                    }

                    // Извлекаем Threads процесса
                    else if (line.find("Threads:") == 0) {
                        process.setThreads(line.substr(8));
                    }

                    // Извлекаем SigQ процесса
                    else if (line.find("SigQ:") == 0) {
                        process.setSigQ(line.substr(5));
                    }

                    // Извлекаем SigPnd процесса
                    else if (line.find("SigPnd:") == 0) {
                        process.setSigPnd(line.substr(7));
                    }

                    // Извлекаем ShdPnd процесса
                    else if (line.find("ShdPnd:") == 0) {
                        process.setShdPnd(line.substr(7));
                    }

                    // Извлекаем SigBlk процесса
                    else if (line.find("SigBlk:") == 0) {
                        process.setSigBlk(line.substr(7));
                    }

                    // Извлекаем SigIgn процесса
                    else if (line.find("SigIgn:") == 0) {
                        process.setSigIgn(line.substr(7));
                    }

                    // Извлекаем SigCgt процесса
                    else if (line.find("SigCgt:") == 0) {
                        process.setSigCgt(line.substr(7));
                    }

                    // Извлекаем CapInh процесса
                    else if (line.find("CapInh:") == 0) {
                        process.setCapInh(line.substr(7));
                    }

                    // Извлекаем CapPrm процесса
                    else if (line.find("CapPrm:") == 0) {
                        process.setCapPrm(line.substr(7));
                    }

                    // Извлекаем CapEff процесса
                    else if (line.find("CapEff:") == 0) {
                        process.setCapEff(line.substr(7));
                    }

                    // Извлекаем CapBnd процесса
                    else if (line.find("CapBnd:") == 0) {
                        process.setCapBnd(line.substr(7));
                    }

                    // Извлекаем CapAmb процесса
                    else if (line.find("CapAmb:") == 0) {
                        process.setCapAmb(line.substr(7));
                    }

                    // Извлекаем NoNewPrivs процесса
                    else if (line.find("NoNewPrivs:") == 0) {
                        process.setNoNewPrivs(line.substr(11));
                    }

                    // Извлекаем Seccomp процесса
                    else if (line.find("Seccomp:") == 0) {
                        process.setSeccomp(line.substr(8));
                    }

                    // Извлекаем Seccomp_filters процесса
                    else if (line.find("Seccomp_filters:") == 0) {
                        process.setSeccomp_filters(line.substr(16));
                    }

                    // Извлекаем Speculation_Store_Bypass процесса
                    else if (line.find("Speculation_Store_Bypass:") == 0) {
                        process.setSpeculation_Store_Bypass(line.substr(25));
                    }

                    // Извлекаем SpeculationIndirectBranch процесса
                    else if (line.find("SpeculationIndirectBranch:") == 0) {
                        process.setSpeculationIndirectBranch(line.substr(26));
                    }

                    // Извлекаем Cpus_allowed процесса
                    else if (line.find("Cpus_allowed:") == 0) {
                        process.setCpus_allowed(line.substr(13));
                    }

                    // Извлекаем Cpus_allowed_list процесса
                    else if (line.find("Cpus_allowed_list:") == 0) {
                        process.setCpus_allowed_list(line.substr(18));
                    }

                    // Извлекаем Mems_allowed процесса
                    else if (line.find("Mems_allowed:") == 0) {
                        process.setMems_allowed(line.substr(13));
                    }

                    // Извлекаем Mems_allowed_list процесса
                    else if (line.find("Mems_allowed_list:") == 0) {
                        process.setMems_allowed_list(line.substr(18));
                    }

                    // Извлекаем voluntary_ctxt_switches процесса
                    else if (line.find("voluntary_ctxt_switches:") == 0) {
                        process.setvoluntary_ctxt_switches(line.substr(24));
                    }

                    // Извлекаем nonvoluntary_ctxt_switches процесса
                    else if (line.find("nonvoluntary_ctxt_switches:") == 0) {
                        process.setnonvoluntary_ctxt_switches(line.substr(27));
                    }

                    // Извлекаем x86_Thread_features процесса
                    else if (line.find("x86_Thread_features:") == 0) {
                        process.setx86_Thread_features(line.substr(20));
                    }

                    // Извлекаем x86_Thread_features_locked процесса
                    else if (line.find("x86_Thread_features_locked:") == 0) {
                        process.setx86_Thread_features_locked(line.substr(27));
                    }

                    /////////////////////////////////////
                    /*Извлечение информации из файла Stat
                     * Первые 2 поля этого файла пропущены из-за сложностей их парсинга
                     *
                     * Памятка значений вектора vectorOfStatFields[i], где каждое i-тое значение означает:
                     * 0 state
                     * 1 ppid - The PID of the parent of this process
                     * 2 pgrp - The process group ID of the process
                     * 3 session - The session ID of the process
                     * 4 tty_nr - The controlling terminal of the process
                     * 5 tpgid - The ID of the foreground process group of the controlling terminal of the process
                     * 6 flags - The kernel flags word of the process
                     * 7 minflt - The number of minor faults the process has made which have not required loading a memory page from disk
                     * 8 cminflt - The number of minor faults that the process's waited-for children have made
                     * 9 majflt - The number of major faults the process has made which have required loading a memory page from disk
                     * 10 cmajflt - The number of major faults that the process's waited-for children have made
                     * 11 utime - Amount of time that this process has been scheduled in user mode, measured in clock ticks
                     * 12 stime - Amount of time that this process has been scheduled in kernel mode, measured in clock ticks
                     * 13 cutime - Amount of time that this process's waited-for children have been scheduled in user mode, measured in clock ticks
                     * 14 cstime - Amount of time that this process's waited-for children have been scheduled in kernel mode, measured in clock ticks
                     * 15 priority - For processes running a real-time scheduling policy, this is the negated scheduling priority, minus one; that is, a number in the range -2 to -100, corresponding to real-time priorities 1 to 99. For processes running under a non-real-time scheduling policy, this is the raw nice value as represented in the kernel
                     * 16 nice - The nice value, a value in the range 19 (low priority) to -20 (high priority)
                     * 17 num_threads - Number of threads in this process
                     * 18 itrealvalue - The time in jiffies before the next SIGALRM is sent to the process due to an interval timer. Since Linux 2.6.17, this field is no longer maintained, and is hard coded as 0
                     * 19 starttime - The time the process started after system boot, measured in clock ticks
                     * 20 vsize - Virtual memory size in bytes
                     * 21 rss - Resident Set Size: number of pages the process has in real memory
                     * 22 rsslim - Current soft limit in bytes on the rss of the process
                     * 23 startcode - The address above which program text can run
                     * 24 endcode - The address below which program text can run
                     * 25 startstack - The address of the start (i.e., bottom) of the stack
                     * 26 kstkesp - The current value of ESP (stack pointer), as found in the kernel stack page for the process
                     * 27 kstkeip - The current EIP (instruction pointer)
                     * 28 signal - The bitmap of pending signals, displayed as a decimal number
                     * 29 blocked - The bitmap of blocked signals, displayed as a decimal number
                     * 30 sigignore - The bitmap of ignored signals, displayed as a decimal number
                     * 31 sigcatch - The bitmap of caught signals, displayed as a decimal number
                     * 32 wchan - This is the "channel" in which the process is waiting.  It is the address of a location in the kernel where the process is sleeping
                     * 33 nswap - Number of pages swapped (not maintained)
                     * 34 cnswap - Cumulative nswap for child processes (not maintained)
                     * 35 exit_signal - Signal to be sent to parent when we die
                     * 36 processor - CPU number last executed on
                     * 37 rt_priority - Real-time scheduling priority, a number in the range 1 to 99 for processes scheduled under a real-time policy, or 0, for non-real-time processes
                     * 38 policy - Scheduling policy
                     * 39 delayacct_blkio_ticks - Aggregated block I/O delays, measured in clock ticks
                     * 40 guest_time - Guest time of the process (time spent running a virtual CPU for a guest operating system), measured in clock ticks
                     * 41 cguest_time - Guest time of the process's children, measured in clock ticks
                     * 42 start_data - Address above which program initialized and uninitialized (BSS) data are placed
                     * 43 end_data - Address below which program initialized and uninitialized (BSS) data are placed
                     * 44 start_brk - Address above which program heap can be expanded with brk(2)
                     * 45 arg_start - Address above which program command-line arguments (argv) are placed
                     * 46 arg_end - Address below program command-line arguments (argv) are placed
                     * 47 env_start - Address above which program environment is placed
                     * 48 env_end - Address below which program environment is placed
                     * 49 exit_code - The thread's exit status in the form reported by waitpid(2).
                     */
                    while (getline(statFileStream, line)) {

                        string fullStatString = line.substr();
                        size_t pos = fullStatString.find(")") + 1;
                        fullStatString = fullStatString.substr(pos);

                        istringstream stringStatStream(fullStatString);
                        string statField;
                        //vector<string> vectorOfStatFields;
                        while (stringStatStream >> statField) {
                            vectorOfStatFields.push_back(statField);
                        }
                    }
                    process.setpgrp(vectorOfStatFields[2]);
                    process.setsession(vectorOfStatFields[3]);
                    process.settty_nr(vectorOfStatFields[4]);
                    process.settpgid(vectorOfStatFields[5]);
                    process.setflags(vectorOfStatFields[6]);
                    process.setminflt(vectorOfStatFields[7]);
                    process.setcminflt(vectorOfStatFields[8]);
                    process.setmajflt(vectorOfStatFields[9]);
                    process.setcmajflt(vectorOfStatFields[10]);
                    process.setutime(vectorOfStatFields[11]);
                    process.setstime(vectorOfStatFields[12]);
                    process.setcutime(vectorOfStatFields[13]);
                    process.setcstime(vectorOfStatFields[14]);
                    process.setpriority(vectorOfStatFields[15]);
                    process.setnice(vectorOfStatFields[16]);
                    process.setnum_threads(vectorOfStatFields[17]);
                    process.setitrealvalue(vectorOfStatFields[18]);
                    process.setstarttime(vectorOfStatFields[19]);
                    process.setvsize(vectorOfStatFields[20]);
                    process.setrss(vectorOfStatFields[21]);
                    process.setrsslim(vectorOfStatFields[22]);
                    process.setstartcode(vectorOfStatFields[23]);
                    process.setendcode(vectorOfStatFields[24]);
                    process.setstartstack(vectorOfStatFields[25]);
                    process.setkstkesp(vectorOfStatFields[26]);
                    process.setkstkeip(vectorOfStatFields[27]);
                    process.setsignal(vectorOfStatFields[28]);
                    process.setblocked(vectorOfStatFields[29]);
                    process.setsigignore(vectorOfStatFields[30]);
                    process.setsigcatch(vectorOfStatFields[31]);
                    process.setwchan(vectorOfStatFields[32]);
                    process.setnswap(vectorOfStatFields[33]);
                    process.setcnswap(vectorOfStatFields[34]);
                    process.setexit_signal(vectorOfStatFields[35]);
                    process.setprocessor(vectorOfStatFields[36]);
                    process.setrt_priority(vectorOfStatFields[37]);
                    process.setpolicy(vectorOfStatFields[38]);
                    process.setdelayacct_blkio_ticks(vectorOfStatFields[39]);
                    process.setguest_time(vectorOfStatFields[40]);
                    process.setcguest_time(vectorOfStatFields[41]);
                    process.setstart_data(vectorOfStatFields[42]);
                    process.setend_data(vectorOfStatFields[43]);
                    process.setstart_brk(vectorOfStatFields[44]);
                    process.setarg_start(vectorOfStatFields[45]);
                    process.setarg_end(vectorOfStatFields[46]);
                    process.setenv_start(vectorOfStatFields[47]);
                    process.setenv_end(vectorOfStatFields[48]);
                    process.setexit_code(vectorOfStatFields[49]);
                }

                processes.push_back(process);
            }
        }
    }
   closedir(procDirectory);
    return processes;
}
