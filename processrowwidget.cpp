#include "processrowwidget.h"

ProcessRowWidget::ProcessRowWidget(int pid, QWidget *parent)
    : QWidget(parent), m_pid(pid) {

    m_terminateButton = new QPushButton("Завершить");
    connect(m_terminateButton, &QPushButton::clicked, this, &ProcessRowWidget::onTerminateButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_terminateButton);
}

void ProcessRowWidget::onTerminateButtonClicked() {
    emit terminateProcess(m_pid);
}

