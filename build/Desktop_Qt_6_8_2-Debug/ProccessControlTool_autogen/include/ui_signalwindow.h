/********************************************************************************
** Form generated from reading UI file 'signalwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNALWINDOW_H
#define UI_SIGNALWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_signalwindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *signalwindow_pidlabel;
    QLabel *signalwindow_pid;
    QHBoxLayout *horizontalLayout_2;
    QLabel *signalwindow_Namelabel;
    QLabel *signalwindow_Name;
    QComboBox *signalwindow_signalComboBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *signalwindow)
    {
        if (signalwindow->objectName().isEmpty())
            signalwindow->setObjectName("signalwindow");
        signalwindow->resize(240, 320);
        verticalLayout = new QVBoxLayout(signalwindow);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        signalwindow_pidlabel = new QLabel(signalwindow);
        signalwindow_pidlabel->setObjectName("signalwindow_pidlabel");
        signalwindow_pidlabel->setMinimumSize(QSize(40, 0));
        signalwindow_pidlabel->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(signalwindow_pidlabel);

        signalwindow_pid = new QLabel(signalwindow);
        signalwindow_pid->setObjectName("signalwindow_pid");
        signalwindow_pid->setMinimumSize(QSize(50, 0));
        signalwindow_pid->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(signalwindow_pid);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        signalwindow_Namelabel = new QLabel(signalwindow);
        signalwindow_Namelabel->setObjectName("signalwindow_Namelabel");
        signalwindow_Namelabel->setMinimumSize(QSize(40, 0));
        signalwindow_Namelabel->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(signalwindow_Namelabel);

        signalwindow_Name = new QLabel(signalwindow);
        signalwindow_Name->setObjectName("signalwindow_Name");

        horizontalLayout_2->addWidget(signalwindow_Name);


        verticalLayout->addLayout(horizontalLayout_2);

        signalwindow_signalComboBox = new QComboBox(signalwindow);
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->addItem(QString());
        signalwindow_signalComboBox->setObjectName("signalwindow_signalComboBox");

        verticalLayout->addWidget(signalwindow_signalComboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(signalwindow);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(signalwindow);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, signalwindow, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, signalwindow, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(signalwindow);
    } // setupUi

    void retranslateUi(QDialog *signalwindow)
    {
        signalwindow->setWindowTitle(QCoreApplication::translate("signalwindow", "Dialog", nullptr));
        signalwindow_pidlabel->setText(QCoreApplication::translate("signalwindow", "pid", nullptr));
        signalwindow_pid->setText(QCoreApplication::translate("signalwindow", "TextLabel", nullptr));
        signalwindow_Namelabel->setText(QCoreApplication::translate("signalwindow", "Name", nullptr));
        signalwindow_Name->setText(QCoreApplication::translate("signalwindow", "TextLabel", nullptr));
        signalwindow_signalComboBox->setItemText(0, QCoreApplication::translate("signalwindow", "1 SIGHUP", nullptr));
        signalwindow_signalComboBox->setItemText(1, QCoreApplication::translate("signalwindow", "2 SIGINT", nullptr));
        signalwindow_signalComboBox->setItemText(2, QCoreApplication::translate("signalwindow", "3 SIGQUIT", nullptr));
        signalwindow_signalComboBox->setItemText(3, QCoreApplication::translate("signalwindow", "4 SIGILL", nullptr));
        signalwindow_signalComboBox->setItemText(4, QCoreApplication::translate("signalwindow", "5 SIGTRAP", nullptr));
        signalwindow_signalComboBox->setItemText(5, QCoreApplication::translate("signalwindow", "6 SIGABRT", nullptr));
        signalwindow_signalComboBox->setItemText(6, QCoreApplication::translate("signalwindow", "7 SIGBUS", nullptr));
        signalwindow_signalComboBox->setItemText(7, QCoreApplication::translate("signalwindow", "8 SIGFPE", nullptr));
        signalwindow_signalComboBox->setItemText(8, QCoreApplication::translate("signalwindow", "9 SIGKILL", nullptr));
        signalwindow_signalComboBox->setItemText(9, QCoreApplication::translate("signalwindow", "10 SIGUSR1", nullptr));
        signalwindow_signalComboBox->setItemText(10, QCoreApplication::translate("signalwindow", "11 SIGSEGV", nullptr));
        signalwindow_signalComboBox->setItemText(11, QCoreApplication::translate("signalwindow", "12 SIGUSR2", nullptr));
        signalwindow_signalComboBox->setItemText(12, QCoreApplication::translate("signalwindow", "13 SIGPIPE", nullptr));
        signalwindow_signalComboBox->setItemText(13, QCoreApplication::translate("signalwindow", "14 SIGALRM", nullptr));
        signalwindow_signalComboBox->setItemText(14, QCoreApplication::translate("signalwindow", "15 SIGTERM", nullptr));
        signalwindow_signalComboBox->setItemText(15, QCoreApplication::translate("signalwindow", "17 SIGCHLD", nullptr));
        signalwindow_signalComboBox->setItemText(16, QCoreApplication::translate("signalwindow", "18 SIGCONT", nullptr));
        signalwindow_signalComboBox->setItemText(17, QCoreApplication::translate("signalwindow", "19 SIGSTOP", nullptr));
        signalwindow_signalComboBox->setItemText(18, QCoreApplication::translate("signalwindow", "20 SIGTSTP", nullptr));
        signalwindow_signalComboBox->setItemText(19, QCoreApplication::translate("signalwindow", "21 SIGTTIN", nullptr));
        signalwindow_signalComboBox->setItemText(20, QCoreApplication::translate("signalwindow", "22 SIGTTOU", nullptr));

        signalwindow_signalComboBox->setPlaceholderText(QCoreApplication::translate("signalwindow", "\320\241\320\270\320\263\320\275\320\260\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signalwindow: public Ui_signalwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNALWINDOW_H
