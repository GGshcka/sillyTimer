#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setText(startTimerString);
    ui->radioButtonTimer->setText(modeTimerString);
    ui->radioButtonAlarm->setText(modeAlarmString);
    ui->radioButtonStopwatch->setText(modeStopwatchString);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{
    QTime targetTime = ui->timeEdit->time();
    QTime currentTime;
    QString modeString;

    switch (MainWindow::timerMode) {
    case 0:
        currentTime = timerTime = timerTime.addSecs(1);
        modeString = modeTimerString + ": ";
        break;
    case 1:
        currentTime = QTime::currentTime();
        modeString = modeAlarmString + ": ";
        break;
    case 2:
        timerTime = timerTime.addSecs(1);
        modeString = modeStopwatchString + ": ";
        break;
    default:
        break;
    }

    if (timerMode < 2) {
        int secondsRemaining = targetTime.secsTo(currentTime); // Вычисляем разницу в секундах

        if (secondsRemaining < 0) {
            // Если заданное время меньше текущего, вычитаем
            secondsRemaining = -secondsRemaining; // Делаем положительным
        }

        // Преобразуем оставшиеся секунды в QTime
        QTime remainingTime = QTime(0, 0).addSecs(secondsRemaining);

        if (remainingTime != QTime(0, 0, 0, 0)) {
            sendNotification(modeString + remainingTime.toString("HH:mm:ss") + " / " + targetTime.toString("HH:mm:ss"), NULL);
        }
        else {
            sendNotification("The countdown is over!", NULL);
            stop();
        }
    }
    else {
        sendNotification(modeString + timerTime.toString("HH:mm:ss"), NULL);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (timerState == false) start();
    else stop();
}

void MainWindow::sendNotification(const QString &summary, const QString &body) {
    QDBusMessage message = QDBusMessage::createMethodCall("org.freedesktop.Notifications",
                                                          "/org/freedesktop/Notifications",
                                                          "org.freedesktop.Notifications",
                                                          "Notify");
    message << QString("sillyTimer") // app_name
            << static_cast<quint32>(QCoreApplication::applicationPid()) // id (uint32)
            << QString() // icon (string)
            << summary // summary (string)
            << body // body (string)
            << QStringList() // actions (array of string)
            << QVariantMap() // hints (dictionary of string to variant)
            << 2000; // expire_timeout (int32)

    QDBusMessage reply = QDBusConnection::sessionBus().call(message, QDBus::Block);
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Error:" << reply.errorMessage();
    }
}

void MainWindow::start() {
    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));

    timer->start(1000);
    timerState = true;

    ui->pushButton->setText(stopTimerString);
    ui->radioButtonTimer->setDisabled(true);
    ui->radioButtonAlarm->setDisabled(true);
    ui->radioButtonStopwatch->setDisabled(true);
}

void MainWindow::stop() {
    timer->stop();
    timerState = false;

    timerTime = QTime(0,0,0);

    disconnect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
    delete timer;

    ui->pushButton->setText(startTimerString);
    ui->radioButtonTimer->setEnabled(true);
    ui->radioButtonAlarm->setEnabled(true);
    ui->radioButtonStopwatch->setEnabled(true);
}

void MainWindow::on_radioButtonTimer_clicked()
{
    ui->radioButtonAlarm->setChecked(false);
    ui->radioButtonStopwatch->setChecked(false);
    ui->timeEdit->setEnabled(true);
    ui->timeEdit->setTime(QTime(0, 15, 0));
    timerMode = 0;
}

void MainWindow::on_radioButtonAlarm_clicked()
{
    ui->radioButtonTimer->setChecked(false);
    ui->radioButtonStopwatch->setChecked(false);
    int currentHour = QTime::currentTime().hour() + 1;
    ui->timeEdit->setEnabled(true);
    ui->timeEdit->setTime(QTime(currentHour, 30, 0));
    timerMode = 1;
}

void MainWindow::on_radioButtonStopwatch_clicked()
{
    ui->radioButtonTimer->setChecked(false);
    ui->radioButtonAlarm->setChecked(false);
    ui->timeEdit->setDisabled(true);
    ui->timeEdit->setTime(QTime(0,0,0));
    timerMode = 2;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    event->ignore();
    this->hide();
}

