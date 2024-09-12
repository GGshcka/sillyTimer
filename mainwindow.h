#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QTimer>
#include <QTime>
#include <QProcess>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void slotTimer();
    //void sendNotification(const QString &title, const QString &message, const int nID, const int msToClose);
    void sendNotification(const QString &summary, const QString &body);
    void stop();
    void start();

    void on_pushButton_clicked();
    void on_radioButtonTimer_clicked();
    void on_radioButtonAlarm_clicked();

    void on_radioButtonStopwatch_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTime timerTime = QTime(0,0,0);
    bool timerState = false;
    int timerMode = 0;
    QString
        startTimerString = QCoreApplication::translate("MainWindow", "Start"),
        stopTimerString = QCoreApplication::translate("MainWindow", "Stop"),
        modeTimerString = QCoreApplication::translate("sillyMods", "Timer"),
        modeAlarmString = QCoreApplication::translate("sillyMods", "Alarm"),
        modeStopwatchString = QCoreApplication::translate("sillyMods", "Stopwatch");
};
#endif // MAINWINDOW_H
