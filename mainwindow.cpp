#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QRegularExpression>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QScrollBar>
#include <QSettings>

#include "processInfo.h"
#include "signalwindow.h"
#include "columnvisibilitywindow.h"
#include "cpuinfo.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
    , proxyModel(new SortFilter(this)) {

    ui->setupUi(this);

    model->setHorizontalHeaderLabels(QStringList() << "Pid" << "Name" << "Umask" << "State" << "PPid"  << "Tgid" << "Ngid" << "TracerPid" << "Uid" << "Gid" << "FDSize" << "Groups" << "NStgid" << "NSpid" << "NSpgid"
                                                   << "NSsid" << "Kthread" << "VmPeak" << "VmSize" << "VmLck" << "VmPin" << "VmHWM" << "VmRSS" << "RssAnon" << "RssFile" << "RssShmem" << "VmData" << "VmStk"
                                                   << "VmExe" << "VmLib" << "VmPTE" << "VmSwap" << "HugetlbPages" << "CoreDumping" << "THP_enabled" << "untag_mask" << "Threads" << "SigQ" << "SigPnd" << "ShdPnd"
                                                   << "SigBlk" << "SigIgn" << "SigCgt" << "CapInh" << "CapPrm" << "CapEff" << "CapBnd" << "CapAmb" << "NoNewPrivs" << "Seccomp" << "Seccomp_filters"
                                                   << "Speculation_Store_Bypass" << "SpeculationIndirectBranch" << "Cpus_allowed" << "Cpus_allowed_list" << "Mems_allowed" << "Mems_allowed_list"
                                                   << "voluntary_ctxt_switches" << "nonvoluntary_ctxt_switches" << "x86_Thread_features" << "x86_Thread_features_locked" << "pgrp" << "session" << "tty_nr"
                                                   << "tpgid" << "flags" << "minflt" << "cminflt" << "majflt" << "cmajflt" << "utime" << "stime" << "cutime" << "cstime" << "priority" << "nice" << "num_threads"
                                                   << "itrealvalue" << "starttime" << "vsize" << "rss" << "rsslim" << "startcode" << "endcode" << "startstack" << "kstkesp" << "kstkeip" << "signal" << "blocked"
                                                   << "sigignore" << "sigcatch" << "wchan" << "nswap" << "cnswap" << "exit_signal" << "processor" << "rt_priority" << "policy" << "delayacct_blkio_ticks"
                                                   << "guest_time" << "cguest_time" << "start_data" << "end_data" << "start_brk" << "arg_start" << "arg_end" << "env_start" << "env_end" << "exit_code" << "%CPU");

    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);

    updateProcessList();

    connect(ui->filterLine, &QLineEdit::textChanged, this, &MainWindow::filterProcesses);

    // Подключаем сигнал нажатия кнопки к слоту завершения процесса
    connect(ui->terminateButton, &QPushButton::clicked, this, &MainWindow::terminateProcess);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateProcessList);
    timer->start(1000);

    ui->tableView->resizeColumnsToContents();
    loadColumnVisibility();
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::updateProcessList() {

    // Сохранение индекса + pid'а выделенной ячейки, чтобы выделение не слетело при обновлении таблицы
    QModelIndex currentIndex = ui->tableView->currentIndex();
    QString currentIndexPid = currentIndex.sibling(currentIndex.row(), 0).data().toString();

    vector<processInfo> vectorOfProcesses = getVectorOfProcesses();

    // Часть вычисления %CPU
    static vector<processInfo> previousVectorOfProcesses = vectorOfProcesses;
    static cpuInfo previousCpu;
    cpuInfo cpu = cpuInfo::getCpuInfo();
    float deltaCpu = cpu.gettotal() - previousCpu.gettotal();

    unordered_map<int, processInfo> previousVectorOfProcessesMap;
    for (auto& proc : previousVectorOfProcesses){
        previousVectorOfProcessesMap[proc.getPid()] = proc;
    }

    model->removeRows(0, model->rowCount());

    // Формирование строк в таблицу
    for (auto& currentProcess : vectorOfProcesses) {
        int pid = currentProcess.getPid();
        auto it = previousVectorOfProcessesMap.find(pid);

        if (it != previousVectorOfProcessesMap.end()) {
            processInfo& prevProc = it->second;
            float deltautime = stoi(currentProcess.getutime()) - stoi(prevProc.getutime()) + stoi(currentProcess.getstime()) - stoi(prevProc.getstime());
            float cpuUsagePercent = deltautime / deltaCpu * 100;

            model->appendRow({
                              new QStandardItem(QString::number(currentProcess.processInfo::getPid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getName())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getUmask())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getState())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getPPid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getTgid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getNgid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getTracerPid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getUid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getGid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getFDSize())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getGroups())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getNStgid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getNSpid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getNSpgid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getNSsid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getKthread())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmPeak())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmSize())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmLck())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmPin())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmHWM())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmRSS())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getRssAnon())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getRssFile())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getRssShmem())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmData())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmStk())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmExe())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmLib())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmPTE())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getVmSwap())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getHugetlbPages())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCoreDumping())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getTHP_enabled())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getuntag_mask())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getThreads())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSigQ())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSigPnd())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getShdPnd())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSigBlk())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSigIgn())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSigCgt())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCapInh())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCapPrm())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCapEff())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCapBnd())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCapAmb())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getNoNewPrivs())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSeccomp())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSeccomp_filters())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSpeculation_Store_Bypass())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getSpeculationIndirectBranch())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCpus_allowed())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getCpus_allowed_list())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getMems_allowed())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getMems_allowed_list())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getvoluntary_ctxt_switches())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getnonvoluntary_ctxt_switches())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getx86_Thread_features())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getx86_Thread_features_locked())),

                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getpgrp())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getsession())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::gettty_nr())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::gettpgid())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getflags())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getminflt())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getcminflt())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getmajflt())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getcmajflt())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getutime())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getstime())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getcutime())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getcstime())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getpriority())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getnice())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getnum_threads())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getitrealvalue())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getstarttime())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getvsize())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getrss())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getrsslim())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getstartcode())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getendcode())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getstartstack())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getkstkesp())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getkstkeip())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getsignal())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getblocked())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getsigignore())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getsigcatch())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getwchan())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getnswap())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getcnswap())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getexit_signal())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getprocessor())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getrt_priority())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getpolicy())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getdelayacct_blkio_ticks())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getguest_time())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getcguest_time())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getstart_data())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getend_data())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getstart_brk())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getarg_start())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getarg_end())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getenv_start())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getenv_end())),
                              new QStandardItem(QString::fromStdString(currentProcess.processInfo::getexit_code())),

                              new QStandardItem(QString::number(cpuUsagePercent, 'f', 2))});
        }
    }
    // Сохранение позиции скролла перед участком кода ниже
    // Из-за участка кода ниже позиция скролла после обновления информации в таблице принудительно прескакивала на выделенный элемент
    int verticalScrollPos = ui->tableView->verticalScrollBar()->value();
    int horizontalScrollPos = ui->tableView->horizontalScrollBar()->value();

    // Поиск pid'а выделенной в прошлом ячейки и установка на неё выделения
    for (int i = 0; i < proxyModel->rowCount(); ++i) {
        QModelIndex index = proxyModel->index(i, 0);
        if (proxyModel->data(index).toString() == currentIndexPid) {
            ui->tableView->setCurrentIndex(index);
        }
    }

    // Восстановление позиции скролла
    ui->tableView->verticalScrollBar()->setValue(verticalScrollPos);
    ui->tableView->horizontalScrollBar()->setValue(horizontalScrollPos);

    previousCpu = cpu;
    previousVectorOfProcesses = vectorOfProcesses;
}


void MainWindow::filterProcesses(const QString &text) {
    QRegularExpression regex(text, QRegularExpression::CaseInsensitiveOption);
    proxyModel->setFilterRegularExpression(regex);
}


void MainWindow::terminateProcess() {
    QModelIndex currentIndex = ui->tableView->currentIndex();
    QString currentIndexPid = currentIndex.sibling(currentIndex.row(), 0).data().toString();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "pid отсутствует", "Необходимо выбрать процесс из списка.");
        return;
    }

    if (QProcess::execute("kill", QStringList() << currentIndexPid) != 0) {
        QMessageBox::warning(this, "Ошибка", "Не удалось завершить процесс.");
        return;
    }

    updateProcessList();
}


void MainWindow::on_pauseStartButton_clicked()
{
    if(ui->pauseStartButton->isChecked()){
        ui->pauseStartButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause));
        timer->start(1000);
    }

    else {
        ui->pauseStartButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
        timer->stop();
    }
}


void MainWindow::on_signalWindowButton_clicked()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    QModelIndex NameIndex = currentIndex.sibling(currentIndex.row(), currentIndex.column() + 1);

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "pid отсутствует", "Необходимо выбрать процесс из списка.");
        return;
    }

    QString pid = proxyModel->data(currentIndex).toString();
    QString Name = proxyModel->data(NameIndex).toString();
    signalwindow signalwindow(pid, Name);
    signalwindow.exec();
}



void MainWindow::on_columnVisibilityWindowButton_clicked()
{
    columnvisibilitywindow cvw;
    connect(&cvw, &columnvisibilitywindow::columnVisibilityWindowClosedSignal, this, &MainWindow::loadColumnVisibility);

    cvw.exec();
}

void MainWindow::loadColumnVisibility()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Sawyer", "ProcessControlTool");
    ui->tableView->setColumnHidden(0, !settings.value("PidCheckBox").toBool());
    ui->tableView->setColumnHidden(1, !settings.value("NameCheckBox").toBool());
    ui->tableView->setColumnHidden(2, !settings.value("UmaskCheckBox").toBool());
    ui->tableView->setColumnHidden(3, !settings.value("StateCheckBox").toBool());
    ui->tableView->setColumnHidden(4, !settings.value("PPidCheckBox").toBool());
    ui->tableView->setColumnHidden(5, !settings.value("TgidCheckBox").toBool());
    ui->tableView->setColumnHidden(6, !settings.value("NgidCheckBox").toBool());
    ui->tableView->setColumnHidden(7, !settings.value("TracerPidCheckBox").toBool());
    ui->tableView->setColumnHidden(8, !settings.value("UidCheckBox").toBool());
    ui->tableView->setColumnHidden(9, !settings.value("GidCheckBox").toBool());
    ui->tableView->setColumnHidden(10, !settings.value("FDSizeCheckBox").toBool());
    ui->tableView->setColumnHidden(11, !settings.value("GroupsCheckBox").toBool());
    ui->tableView->setColumnHidden(12, !settings.value("NStgidCheckBox").toBool());
    ui->tableView->setColumnHidden(13, !settings.value("NSpidCheckBox").toBool());
    ui->tableView->setColumnHidden(14, !settings.value("NSpgidCheckBox").toBool());
    ui->tableView->setColumnHidden(15, !settings.value("NSsidCheckBox").toBool());
    ui->tableView->setColumnHidden(16, !settings.value("KthreadCheckBox").toBool());
    ui->tableView->setColumnHidden(17, !settings.value("VmPeakCheckBox").toBool());
    ui->tableView->setColumnHidden(18, !settings.value("VmSizeCheckBox").toBool());
    ui->tableView->setColumnHidden(19, !settings.value("VmLckCheckBox").toBool());
    ui->tableView->setColumnHidden(20, !settings.value("VmPinCheckBox").toBool());
    ui->tableView->setColumnHidden(21, !settings.value("VmHWMCheckBox").toBool());
    ui->tableView->setColumnHidden(22, !settings.value("VmRSSCheckBox").toBool());
    ui->tableView->setColumnHidden(23, !settings.value("RssAnonCheckBox").toBool());
    ui->tableView->setColumnHidden(24, !settings.value("RssFileCheckBox").toBool());
    ui->tableView->setColumnHidden(25, !settings.value("RssShmemCheckBox").toBool());
    ui->tableView->setColumnHidden(26, !settings.value("VmDataCheckBox").toBool());
    ui->tableView->setColumnHidden(27, !settings.value("VmStkCheckBox").toBool());
    ui->tableView->setColumnHidden(28, !settings.value("VmExeCheckBox").toBool());
    ui->tableView->setColumnHidden(29, !settings.value("VmLibCheckBox").toBool());
    ui->tableView->setColumnHidden(30, !settings.value("VmPTECheckBox").toBool());
    ui->tableView->setColumnHidden(31, !settings.value("VmSwapCheckBox").toBool());
    ui->tableView->setColumnHidden(32, !settings.value("HugetlbPagesCheckBox").toBool());
    ui->tableView->setColumnHidden(33, !settings.value("CoreDumpingCheckBox").toBool());
    ui->tableView->setColumnHidden(34, !settings.value("THP_enabledCheckBox").toBool());
    ui->tableView->setColumnHidden(35, !settings.value("untag_maskCheckBox").toBool());
    ui->tableView->setColumnHidden(36, !settings.value("ThreadsCheckBox").toBool());
    ui->tableView->setColumnHidden(37, !settings.value("SigQCheckBox").toBool());
    ui->tableView->setColumnHidden(38, !settings.value("SigPndCheckBox").toBool());
    ui->tableView->setColumnHidden(39, !settings.value("ShdPndCheckBox").toBool());
    ui->tableView->setColumnHidden(40, !settings.value("SigBlkCheckBox").toBool());
    ui->tableView->setColumnHidden(41, !settings.value("SigIgnCheckBox").toBool());
    ui->tableView->setColumnHidden(42, !settings.value("SigCgtCheckBox").toBool());
    ui->tableView->setColumnHidden(43, !settings.value("CapInhCheckBox").toBool());
    ui->tableView->setColumnHidden(44, !settings.value("CapPrmCheckBox").toBool());
    ui->tableView->setColumnHidden(45, !settings.value("CapEffCheckBox").toBool());
    ui->tableView->setColumnHidden(46, !settings.value("CapBndCheckBox").toBool());
    ui->tableView->setColumnHidden(47, !settings.value("CapAmbCheckBox").toBool());
    ui->tableView->setColumnHidden(48, !settings.value("NoNewPrivsCheckBox").toBool());
    ui->tableView->setColumnHidden(49, !settings.value("SeccompCheckBox").toBool());
    ui->tableView->setColumnHidden(50, !settings.value("Seccomp_filtersCheckBox").toBool());
    ui->tableView->setColumnHidden(51, !settings.value("Speculation_Store_BypassCheckBox").toBool());
    ui->tableView->setColumnHidden(52, !settings.value("SpeculationIndirectBranchCheckBox").toBool());
    ui->tableView->setColumnHidden(53, !settings.value("Cpus_allowedCheckBox").toBool());
    ui->tableView->setColumnHidden(54, !settings.value("Cpus_allowed_listCheckBox").toBool());
    ui->tableView->setColumnHidden(55, !settings.value("Mems_allowedCheckBox").toBool());
    ui->tableView->setColumnHidden(56, !settings.value("Mems_allowed_listCheckBox").toBool());
    ui->tableView->setColumnHidden(57, !settings.value("voluntary_ctxt_switchesCheckBox").toBool());
    ui->tableView->setColumnHidden(58, !settings.value("nonvoluntary_ctxt_switchesCheckBox").toBool());
    ui->tableView->setColumnHidden(59, !settings.value("x86_Thread_featuresCheckBox").toBool());
    ui->tableView->setColumnHidden(60, !settings.value("x86_Thread_features_lockedCheckBox").toBool());
    ui->tableView->setColumnHidden(61, !settings.value("pgrpCheckBox").toBool());
    ui->tableView->setColumnHidden(62, !settings.value("sessionCheckBox").toBool());
    ui->tableView->setColumnHidden(63, !settings.value("tty_nrCheckBox").toBool());
    ui->tableView->setColumnHidden(64, !settings.value("tpgidCheckBox").toBool());
    ui->tableView->setColumnHidden(65, !settings.value("flagsCheckBox").toBool());
    ui->tableView->setColumnHidden(66, !settings.value("minfltCheckBox").toBool());
    ui->tableView->setColumnHidden(67, !settings.value("cminfltCheckBox").toBool());
    ui->tableView->setColumnHidden(68, !settings.value("majfltCheckBox").toBool());
    ui->tableView->setColumnHidden(69, !settings.value("cmajfltCheckBox").toBool());
    ui->tableView->setColumnHidden(70, !settings.value("utimeCheckBox").toBool());
    ui->tableView->setColumnHidden(71, !settings.value("stimeCheckBox").toBool());
    ui->tableView->setColumnHidden(72, !settings.value("cutimeCheckBox").toBool());
    ui->tableView->setColumnHidden(73, !settings.value("cstimeCheckBox").toBool());
    ui->tableView->setColumnHidden(74, !settings.value("priorityCheckBox").toBool());
    ui->tableView->setColumnHidden(75, !settings.value("niceCheckBox").toBool());
    ui->tableView->setColumnHidden(76, !settings.value("num_threadsCheckBox").toBool());
    ui->tableView->setColumnHidden(77, !settings.value("itrealvalueCheckBox").toBool());
    ui->tableView->setColumnHidden(78, !settings.value("starttimeCheckBox").toBool());
    ui->tableView->setColumnHidden(79, !settings.value("vsizeCheckBox").toBool());
    ui->tableView->setColumnHidden(80, !settings.value("rssCheckBox").toBool());
    ui->tableView->setColumnHidden(81, !settings.value("rsslimCheckBox").toBool());
    ui->tableView->setColumnHidden(82, !settings.value("startcodeCheckBox").toBool());
    ui->tableView->setColumnHidden(83, !settings.value("endcodeCheckBox").toBool());
    ui->tableView->setColumnHidden(84, !settings.value("startstackCheckBox").toBool());
    ui->tableView->setColumnHidden(85, !settings.value("kstkespCheckBox").toBool());
    ui->tableView->setColumnHidden(86, !settings.value("kstkeipCheckBox").toBool());
    ui->tableView->setColumnHidden(87, !settings.value("signalCheckBox").toBool());
    ui->tableView->setColumnHidden(88, !settings.value("blockedCheckBox").toBool());
    ui->tableView->setColumnHidden(89, !settings.value("sigignoreCheckBox").toBool());
    ui->tableView->setColumnHidden(90, !settings.value("sigcatchCheckBox").toBool());
    ui->tableView->setColumnHidden(91, !settings.value("wchanCheckBox").toBool());
    ui->tableView->setColumnHidden(92, !settings.value("nswapCheckBox").toBool());
    ui->tableView->setColumnHidden(93, !settings.value("cnswapCheckBox").toBool());
    ui->tableView->setColumnHidden(94, !settings.value("exit_signalCheckBox").toBool());
    ui->tableView->setColumnHidden(95, !settings.value("processorCheckBox").toBool());
    ui->tableView->setColumnHidden(96, !settings.value("rt_priorityCheckBox").toBool());
    ui->tableView->setColumnHidden(97, !settings.value("policyCheckBox").toBool());
    ui->tableView->setColumnHidden(98, !settings.value("delayacct_blkio_ticksCheckBox").toBool());
    ui->tableView->setColumnHidden(99, !settings.value("guest_timeCheckBox").toBool());
    ui->tableView->setColumnHidden(100, !settings.value("cguest_timeCheckBox").toBool());
    ui->tableView->setColumnHidden(101, !settings.value("start_dataCheckBox").toBool());
    ui->tableView->setColumnHidden(102, !settings.value("end_dataCheckBox").toBool());
    ui->tableView->setColumnHidden(103, !settings.value("start_brkCheckBox").toBool());
    ui->tableView->setColumnHidden(104, !settings.value("arg_startCheckBox").toBool());
    ui->tableView->setColumnHidden(105, !settings.value("arg_endCheckBox").toBool());
    ui->tableView->setColumnHidden(106, !settings.value("env_startCheckBox").toBool());
    ui->tableView->setColumnHidden(107, !settings.value("env_endCheckBox").toBool());
    ui->tableView->setColumnHidden(108, !settings.value("exit_codeCheckBox").toBool());
    ui->tableView->setColumnHidden(109, !settings.value("%CPUCheckBox").toBool());
}

