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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
    , proxyModel(new Filter(this)) {

    ui->setupUi(this);

    model->setHorizontalHeaderLabels(QStringList() << "pid" << "Name" << "Umask" << "State" << "PPid"  << "Tgid" << "Ngid" << "TracerPid" << "Uid" << "Gid" << "FDSize" << "Groups" << "NStgid" << "NSpid" << "NSpgid"
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
    //ui->tableView->setColumnHidden(1, 1);
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

