#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "filter.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void updateProcessList();
    void filterProcesses(const QString &text); // Новый слот для фильтрации
    void terminateProcess();
    void on_pauseStartButton_clicked();
    void on_signalWindowButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    Filter *proxyModel; // Прокси-модель
    QTimer *timer;
};

#endif // MAINWINDOW_H

