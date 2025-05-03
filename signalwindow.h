#ifndef SIGNALWINDOW_H
#define SIGNALWINDOW_H

#include <QDialog>

namespace Ui {
class signalwindow;
}

class signalwindow : public QDialog
{
    Q_OBJECT

public:
    explicit signalwindow(QString pidLabelText, QString NameLabelText, QWidget *parent = nullptr);
    ~signalwindow();
    QString getPidOfCurrentIndex();

private slots:

    void on_buttonBox_accepted();

private:
    Ui::signalwindow *ui;
    QString pidLabelText;
    QString NameLabelText;
};

#endif // SIGNALWINDOW_H
