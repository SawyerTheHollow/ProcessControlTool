#ifndef COLUMNVISIBILITYWINDOW_H
#define COLUMNVISIBILITYWINDOW_H

#include <QDialog>

namespace Ui {
class columnvisibilitywindow;
}

class columnvisibilitywindow : public QDialog
{
    Q_OBJECT

public:
    explicit columnvisibilitywindow(QWidget *parent = nullptr);
    ~columnvisibilitywindow();

signals:
    void columnVisibilityWindowClosedSignal();

private slots:
    void saveCheckBoxSettings();
    void loadCheckBoxSettings();

    void on_buttonBox_accepted();

private:
    Ui::columnvisibilitywindow *ui;
};

#endif // COLUMNVISIBILITYWINDOW_H
