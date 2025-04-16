#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "processInfo.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
    , proxyModel(new Filter(this)) {

    ui->setupUi(this);

    model->setHorizontalHeaderLabels(QStringList() << "PID" << "Name" << "State" << "PPid" << "Umask");

    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);

    updateProcessList();

    ui->filterLine->setPlaceholderText("Фильтр");

    connect(ui->filterLine, &QLineEdit::textChanged, this, &MainWindow::filterProcesses);

    // Подключаем сигнал нажатия кнопки к слоту завершения процесса
    connect(ui->terminateButton, &QPushButton::clicked, this, &MainWindow::terminateProcess);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateProcessList);
    timer->start(1000);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateProcessList() {
    vector<processInfo> vectorOfProcesses = getVectorOfProcesses();

    model->removeRows(0, model->rowCount()); // Очищаем модель перед обновлением

    for (int i = 0; i < vectorOfProcesses.size(); i++) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::number(vectorOfProcesses[i].processInfo::getPid()))); // PID
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getName()))); // Имя процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getState()))); // State процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getPPid()))); // PPid процесса
        items.append(new QStandardItem(QString::fromStdString(vectorOfProcesses[i].processInfo::getUmask()))); // Umask процесса

        model->appendRow(items);
    }
}

void MainWindow::filterProcesses(const QString &text) {
    QRegularExpression regex(text, QRegularExpression::CaseInsensitiveOption);
    proxyModel->setFilterRegularExpression(regex);
}

void MainWindow::terminateProcess() {
    QModelIndex currentIndex = ui->tableView->currentIndex();

    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите процесс для завершения.");
        return;
    }

    int pid = model->item(currentIndex.row(), 0)->text().toInt();

    if (QProcess::execute("kill", QStringList() << QString::number(pid)) != 0) {
        QMessageBox::warning(this, "Ошибка", "Не удалось завершить процесс.");
        return;
    }

    updateProcessList();
}
