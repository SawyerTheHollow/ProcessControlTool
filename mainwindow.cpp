#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "processInfo.h"
#include "signalwindow.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QScrollBar>
#include <QSettings>


#include <QDebug>
#include "columnvisibilitywindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
    , proxyModel(new Filter(this)) {

    ui->setupUi(this);

    //connect(columnvisibilitywindow::columnvisibilitywindow);

    model->setHorizontalHeaderLabels(QStringList() << "Pid" << "Name" << "Umask" << "State" << "PPid"  << "Tgid" << "Ngid" << "TracerPid" << "Uid" << "Gid" << "FDSize" << "Groups" << "NStgid" << "NSpid" << "NSpgid"
                                                   << "NSsid" << "Kthread" << "VmPeak" << "VmSize" << "VmLck" << "VmPin" << "VmHWM" << "VmRSS" << "RssAnon" << "RssFile" << "RssShmem" << "VmData" << "VmStk"
                                                   << "VmExe" << "VmLib" << "VmPTE" << "VmSwap" << "HugetlbPages" << "CoreDumping" << "THP_enabled" << "untag_mask" << "Threads" << "SigQ" << "SigPnd" << "ShdPnd"
                                                   << "SigBlk" << "SigIgn" << "SigCgt" << "CapInh" << "CapPrm" << "CapEff" << "CapBnd" << "CapAmb" << "NoNewPrivs" << "Seccomp" << "Seccomp_filters"
                                                   << "Speculation_Store_Bypass" << "SpeculationIndirectBranch" << "Cpus_allowed" << "Cpus_allowed_list" << "Mems_allowed" << "Mems_allowed_list"
                                                   << "voluntary_ctxt_switches" << "nonvoluntary_ctxt_switches" << "x86_Thread_features" << "x86_Thread_features_locked" << "pgrp" << "session" << "tty_nr"
                                                   << "tpgid" << "flags" << "minflt" << "cminflt" << "majflt" << "cmajflt" << "utime" << "stime" << "cutime" << "cstime" << "priority" << "nice" << "num_threads"
                                                   << "itrealvalue" << "starttime" << "vsize" << "rss" << "rsslim" << "startcode" << "endcode" << "startstack" << "kstkesp" << "kstkeip" << "signal" << "blocked"
                                                   << "sigignore" << "sigcatch" << "wchan" << "nswap" << "cnswap" << "exit_signal" << "processor" << "rt_priority" << "policy" << "delayacct_blkio_ticks"
                                                   << "guest_time" << "cguest_time" << "start_data" << "end_data" << "start_brk" << "arg_start" << "arg_end" << "env_start" << "env_end" << "exit_code");

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

    model->removeRows(0, model->rowCount()); // Очищаем модель перед обновлением

    for (int i = 0; i < vectorOfProcesses.size(); i++) {
        QList<QStandardItem *> items;

        items.append(new QStandardItem(QString::number(vectorOfProcesses[i].processInfo::getPid()))); // pid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getName()))); // Name процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getUmask()))); // Umask процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getState()))); // State процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getPPid()))); // PPid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getTgid()))); // Tgid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getNgid()))); // Ngid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getTracerPid()))); // TracerPid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getUid()))); // Uid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getGid()))); // Gid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getFDSize()))); // FDSize процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getGroups()))); // Groups процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getNStgid()))); // NStgid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getNSpid()))); // NSpid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getNSpgid()))); // NSpgid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getNSsid()))); // NSsid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getKthread()))); // Kthread процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmPeak()))); // VmPeak процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmSize()))); // VmSize процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmLck()))); // VmLck процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmPin()))); // VmPin процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmHWM()))); // VmHWM процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmRSS()))); // VmRSS процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getRssAnon()))); // RssAnon процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getRssFile()))); // RssFile процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getRssShmem()))); // RssShmem процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmData()))); // VmData процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmStk()))); // VmStk процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmExe()))); // VmExe процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmLib()))); // VmLib процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmPTE()))); // VmPTE процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getVmSwap()))); // VmSwap процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getHugetlbPages()))); // HugetlbPages процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCoreDumping()))); // CoreDumping процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getTHP_enabled()))); // THP_enabled процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getuntag_mask()))); // untag_mask процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getThreads()))); // Threads процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSigQ()))); // SigQ процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSigPnd()))); // SigPnd процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getShdPnd()))); // ShdPnd процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSigBlk()))); // SigBlk процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSigIgn()))); // SigIgn процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSigCgt()))); // SigCgt процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCapInh()))); // CapInh процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCapPrm()))); // CapPrm процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCapEff()))); // CapEff процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCapBnd()))); // CapBnd процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCapAmb()))); // CapAmb процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getNoNewPrivs()))); // NoNewPrivs процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSeccomp()))); // Seccomp процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSeccomp_filters()))); // Seccomp_filters процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSpeculation_Store_Bypass()))); // Speculation_Store_Bypass процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getSpeculationIndirectBranch()))); // SpeculationIndirectBranch процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCpus_allowed()))); // Cpus_allowed процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getCpus_allowed_list()))); // Cpus_allowed_list процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getMems_allowed()))); // Mems_allowed процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getMems_allowed_list()))); // Mems_allowed_list процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getvoluntary_ctxt_switches()))); // voluntary_ctxt_switches процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getnonvoluntary_ctxt_switches()))); // nonvoluntary_ctxt_switches процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getx86_Thread_features()))); // x86_Thread_features процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getx86_Thread_features_locked()))); // x86_Thread_features_locked процесса

        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getpgrp())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getsession())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::gettty_nr())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::gettpgid())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getflags())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getminflt())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getcminflt())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getmajflt())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getcmajflt())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getutime())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getstime())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getcutime())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getcstime())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getpriority())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getnice())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getnum_threads())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getitrealvalue())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getstarttime())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getvsize())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getrss())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getrsslim())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getstartcode())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getendcode())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getstartstack())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getkstkesp())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getkstkeip())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getsignal())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getblocked())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getsigignore())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getsigcatch())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getwchan())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getnswap())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getcnswap())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getexit_signal())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getprocessor())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getrt_priority())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getpolicy())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getdelayacct_blkio_ticks())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getguest_time())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getcguest_time())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getstart_data())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getend_data())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getstart_brk())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getarg_start())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getarg_end())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getenv_start())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getenv_end())));
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getexit_code())));

        model->appendRow(items);
    }
    // Костыль для сохранения позиции скролла перед участком кода ниже
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
}


void MainWindow::filterProcesses(const QString &text) {
    QRegularExpression regex(text, QRegularExpression::CaseInsensitiveOption);
    proxyModel->setFilterRegularExpression(regex);
}


void MainWindow::terminateProcess() {
    QModelIndex currentIndex = ui->tableView->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "pid отсутствует", "Необходимо выбрать процесс из списка.");
        return;
    }

    QString pid = proxyModel->data(currentIndex).toString();

    if (QProcess::execute("kill", QStringList() << pid) != 0) {
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
}

