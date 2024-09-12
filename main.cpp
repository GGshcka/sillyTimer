#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QSharedMemory>
#include <QLocalServer>
#include <QLocalSocket>
#include <QDebug>

const QString serverName = "sillyTimerServer";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Проверка на наличие запущенной копии
    QSharedMemory sharedMemory("sillyTimer");
    if (sharedMemory.attach()) {
        // Если копия запущена, отправляем сообщение
        QLocalSocket socket;
        socket.connectToServer(serverName);
        if (socket.waitForConnected()) {
            socket.write("show");
            socket.flush();
            socket.waitForBytesWritten();
            socket.disconnectFromServer();
        }
        return 0;
    }
    if (!sharedMemory.create(1)) {
        // Если не удалось создать разделяемую память, завершаем работу
        return 1;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        if (translator.load("sillyTimer_" + QLocale(locale).name() + ".qm", ":/locales/")) {
            qDebug("translator loaded...");
            a.installTranslator(&translator);
            break;
        }
        qDebug() << QLocale(locale).name();
    }

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
    trayIcon->setIcon(QIcon(":/icon/tray/icon.png"));

    MainWindow *mainWindow = new MainWindow();

    // Создаем локальный сервер
    QLocalServer server;
    server.listen(serverName);
    QObject::connect(&server, &QLocalServer::newConnection, [&]() {
        QLocalSocket *clientConnection = server.nextPendingConnection();
        QObject::connect(clientConnection, &QLocalSocket::readyRead, [clientConnection, mainWindow]() {
            clientConnection->readAll(); // Читаем данные (в данном случае просто игнорируем)
            mainWindow->show(); // Показываем главное окно
            clientConnection->disconnectFromServer();
        });
    });

    QMenu *menu = new QMenu();
    menu->addAction(QCoreApplication::translate("trayContext", "Open"), [mainWindow]() { mainWindow->show(); });
    menu->addAction(QCoreApplication::translate("trayContext", "Quit"), &a, &QApplication::quit);

    trayIcon->setContextMenu(menu);
    trayIcon->setVisible(true);

    QObject::connect(trayIcon, &QSystemTrayIcon::activated, [mainWindow](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            mainWindow->show();
        }
    });

    mainWindow->show();

    QObject::connect(&a, &QApplication::aboutToQuit, [&]() {
        sharedMemory.detach(); // Освобождаем разделяемую память
        server.close(); // Закрываем локальный сервер
    });

    return a.exec();
}
