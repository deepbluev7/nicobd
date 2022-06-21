#include <iostream>

#include <BluezQt/Manager>
#include <BluezQt/PendingCall>
#include <BluezQt/InitManagerJob>
#include <QCoreApplication>

#include "serialportprofile.h"

#define PROJECT_NAME "nicobd"

int
main(int argc, char **argv)
{
    if (argc != 1) {
        std::cout << argv[0] << "takes no arguments.\n";
        return 1;
}   std::cout << "This is project " << PROJECT_NAME << ".\n";

    QCoreApplication app(argc, argv);

    BluezQt::Manager *manager = new BluezQt::Manager();
    BluezQt::InitManagerJob *initJob = manager->init();
    initJob->exec();

    if (initJob->error()) {
        qWarning() << "Error initializing manager:" << initJob->errorText();
        return 1;
    }

    BluezQt::PendingCall *spp = manager->registerProfile(new SerialPortProfile(&app));
    spp->waitForFinished();

    if (spp->error()) {
        qWarning() << "Error registering profile" << spp->errorText();
        return 1;
    }

    qDebug() << "Profile registered";

    return app.exec();
}
