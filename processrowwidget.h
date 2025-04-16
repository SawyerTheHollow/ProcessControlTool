#ifndef PROCESSROWWIDGET_H
#define PROCESSROWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ProcessRowWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProcessRowWidget(int pid, QWidget *parent = nullptr);

signals:
    void terminateProcess(int pid);

private slots:
    void onTerminateButtonClicked();

private:
    int m_pid;
    QPushButton *m_terminateButton;
};

#endif // PROCESSROWWIDGET_H
