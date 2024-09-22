/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTimeEdit *timeEdit;
    QPushButton *pushButton;
    QRadioButton *radioButtonAlarm;
    QRadioButton *radioButtonTimer;
    QRadioButton *radioButtonStopwatch;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(166, 170);
        MainWindow->setMinimumSize(QSize(166, 170));
        MainWindow->setMaximumSize(QSize(200, 170));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(115, 115, 115);\n"
"selection-color: rgb(255, 255, 255);\n"
"border-color: rgb(199, 199, 199);\n"
"color: rgb(255, 255, 255);"));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MainWindow->setTabShape(QTabWidget::TabShape::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setGeometry(QRect(20, 10, 126, 24));
        timeEdit->setStyleSheet(QString::fromUtf8(""));
        timeEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        timeEdit->setTime(QTime(0, 15, 0));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 50, 126, 23));
        radioButtonAlarm = new QRadioButton(centralwidget);
        radioButtonAlarm->setObjectName("radioButtonAlarm");
        radioButtonAlarm->setGeometry(QRect(20, 100, 131, 20));
        radioButtonAlarm->setChecked(false);
        radioButtonTimer = new QRadioButton(centralwidget);
        radioButtonTimer->setObjectName("radioButtonTimer");
        radioButtonTimer->setGeometry(QRect(20, 80, 131, 20));
        radioButtonTimer->setChecked(true);
        radioButtonStopwatch = new QRadioButton(centralwidget);
        radioButtonStopwatch->setObjectName("radioButtonStopwatch");
        radioButtonStopwatch->setGeometry(QRect(20, 120, 131, 20));
        radioButtonStopwatch->setChecked(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 166, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "sillyTimer", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("MainWindow", "HH:mm:ss", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "startTimerString", nullptr));
        radioButtonAlarm->setText(QCoreApplication::translate("MainWindow", "Alarm", nullptr));
        radioButtonTimer->setText(QCoreApplication::translate("MainWindow", "Timer", nullptr));
        radioButtonStopwatch->setText(QCoreApplication::translate("MainWindow", "Stopwatch", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
