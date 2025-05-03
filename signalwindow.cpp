#include "signalwindow.h"
#include "ui_signalwindow.h"
#include <QProcess>
#include <QMessageBox>

#include <QDebug>

signalwindow::signalwindow(QString pidLabelText, QString NameLabelText, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signalwindow)
{
    ui->setupUi(this);
    ui->signalwindow_pid->setText(pidLabelText);
    ui->signalwindow_Name->setText(NameLabelText);
}

signalwindow::~signalwindow()
{
    delete ui;
}

QString signalwindow::getPidOfCurrentIndex(){
    return pidLabelText;
}


void signalwindow::on_buttonBox_accepted()
{
    QString pid = ui->signalwindow_pid->text();
    int currentComboBoxIndex = ui->signalwindow_signalComboBox->currentIndex();

    switch (currentComboBoxIndex) {

        // 1 SIGHUP Hangup (разрыв соединения)
    case 0:
        if (QProcess::execute("kill", QStringList("-SIGHUP") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGHUP.");
            return;
        }
        break;

        // 2 SIGINT Interrupt (прерывание, обычно Ctrl+C)
    case 1:
        if (QProcess::execute("kill", QStringList("-SIGINT") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGINT.");
            return;
        }
        break;

        // 3 SIGQUIT Quit (выход с дампом памяти)
    case 2:
        if (QProcess::execute("kill", QStringList("-SIGQUIT") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGQUIT.");
            return;
        }
        break;

        // 4 SIGILL Illegal instruction (недопустимая инструкция)
    case 3:
        if (QProcess::execute("kill", QStringList("-SIGILL") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGILL.");
            return;
        }
        break;

        // 5 SIGTRAP Trace trap (точка останова отладчика)
    case 4:
        if (QProcess::execute("kill", QStringList("-SIGTRAP") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGTRAP.");
            return;
        }
        break;

        // 6 SIGABRT Abort (аварийное завершение)
    case 5:
        if (QProcess::execute("kill", QStringList("-SIGABRT") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGABRT.");
            return;
        }
        break;

        // 7 SIGBUS Bus error (ошибка доступа к памяти)
    case 6:
        if (QProcess::execute("kill", QStringList("-SIGBUS") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGBUS.");
            return;
        }
        break;

        // 8 SIGFPE Floating point exception (арифметическая ошибка)
    case 7:
        if (QProcess::execute("kill", QStringList("-SIGFPE") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGFPE.");
            return;
        }
        break;

        // 9 SIGKILL Kill (немедленное завершение процесса)
    case 8:
        if (QProcess::execute("kill", QStringList("-SIGKILL") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGKILL.");
            return;
        }
        break;

        // 10 SIGUSR1 User1 (пользовательский сигнал 1)
    case 9:
        if (QProcess::execute("kill", QStringList("-SIGUSR1") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGUSR1.");
            return;
        }
        break;

        // 11 SIGSEGV 	Segmentation fault (ошибка сегментации памяти)
    case 10:
        if (QProcess::execute("kill", QStringList("-SIGSEGV") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGSEGV.");
            return;
        }
        break;

        // 12 SIGUSR2 User2 (пользовательский сигнал 2)
    case 11:
        if (QProcess::execute("kill", QStringList("-SIGUSR2") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGUSR2.");
            return;
        }
        break;

        // 13 SIGPIPE Broken pipe (запись в закрытый канал)
    case 12:
        if (QProcess::execute("kill", QStringList("-SIGPIPE") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGPIPE.");
            return;
        }
        break;

        // 14 SIGALRM Alarm clock (таймер)
    case 13:
        if (QProcess::execute("kill", QStringList("-SIGALRM") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGALRM.");
            return;
        }
        break;

        // 15 SIGTERM Termination request (запрос на завершение)
    case 14:
        if (QProcess::execute("kill", QStringList("-SIGTERM") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGTERM.");
            return;
        }
        break;

        // 17 SIGCHLD Child (изменение состояния дочернего процесса)
    case 16:
        if (QProcess::execute("kill", QStringList("-SIGCHLD") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGCHLD.");
            return;
        }
        break;

        // 18 SIGCONT Continue (продолжить выполнение после остановки)
    case 17:
        if (QProcess::execute("kill", QStringList("-SIGCONT") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGCONT.");
            return;
        }
        break;

        // 19 SIGSTOP Stop (остановить выполнение процесса)
    case 18:
        if (QProcess::execute("kill", QStringList("-SIGSTOP") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGSTOP.");
            return;
        }
        break;

        // 20 SIGTSTP Terminal stop (остановка с терминала (обычно Ctrl+Z))
    case 19:
        if (QProcess::execute("kill", QStringList("-SIGTSTP") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGTSTP.");
            return;
        }
        break;

        // 21 SIGTTIN Terminal input (попытка чтения с терминала в фоне)
    case 20:
        if (QProcess::execute("kill", QStringList("-SIGTTIN") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGTTIN.");
            return;
        }
        break;

        // 22 SIGTTOU Terminal output (попытка записи в терминал в фоне)
    case 21:
        if (QProcess::execute("kill", QStringList("-SIGTTOU") << pid) != 0) {
            QMessageBox::warning(this, "Ошибка", "Не удалось применить SIGTTOU.");
            return;
        }
        break;
    }
}


