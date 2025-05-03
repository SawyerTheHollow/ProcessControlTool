/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *filterLine;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *pauseStartButton;
    QPushButton *terminateButton;
    QPushButton *signalWindowButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        filterLine = new QLineEdit(centralwidget);
        filterLine->setObjectName("filterLine");

        verticalLayout->addWidget(filterLine);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setLineWidth(1);
        tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableView->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        tableView->setGridStyle(Qt::PenStyle::SolidLine);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pauseStartButton = new QPushButton(centralwidget);
        pauseStartButton->setObjectName("pauseStartButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pauseStartButton->sizePolicy().hasHeightForWidth());
        pauseStartButton->setSizePolicy(sizePolicy);
        pauseStartButton->setMinimumSize(QSize(25, 0));
        pauseStartButton->setMaximumSize(QSize(50, 16777215));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        pauseStartButton->setIcon(icon);
        pauseStartButton->setCheckable(true);

        horizontalLayout->addWidget(pauseStartButton);

        terminateButton = new QPushButton(centralwidget);
        terminateButton->setObjectName("terminateButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(255);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(terminateButton->sizePolicy().hasHeightForWidth());
        terminateButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(terminateButton);

        signalWindowButton = new QPushButton(centralwidget);
        signalWindowButton->setObjectName("signalWindowButton");
        signalWindowButton->setMinimumSize(QSize(25, 0));
        signalWindowButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(signalWindowButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        filterLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\273\321\214\321\202\321\200", nullptr));
        pauseStartButton->setText(QString());
        terminateButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\262\320\265\321\200\321\210\320\270\321\202\321\214 \320\277\321\200\320\276\321\206\320\265\321\201\321\201", nullptr));
#if QT_CONFIG(tooltip)
        signalWindowButton->setToolTip(QCoreApplication::translate("MainWindow", "\320\224\321\200\321\203\320\263\320\270\320\265 \321\201\320\270\320\263\320\275\320\260\320\273\321\213", nullptr));
#endif // QT_CONFIG(tooltip)
        signalWindowButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
