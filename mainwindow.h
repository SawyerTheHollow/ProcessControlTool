#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "sortfilter.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:

    void loadColumnVisibility();

private slots:
    void updateProcessList();
    void filterProcesses(const QString &text);
    void terminateProcess();
    void on_pauseStartButton_clicked();
    void on_signalWindowButton_clicked();
    void on_columnVisibilityWindowButton_clicked();


private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    SortFilter *proxyModel; // Прокси-модель
    QTimer *timer;
};

#endif // MAINWINDOW_H

