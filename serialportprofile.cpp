#include "serialportprofile.h"

#include <BluezQt/Device>
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QDBusUnixFileDescriptor>
#include <QDebug>
#include <QTimer>

SerialPortProfile::SerialPortProfile(QObject *parent)
  : BluezQt::Profile(parent)
{
    setName(QStringLiteral("Serial Port"));
    setChannel(22);
    setLocalRole(LocalRole::ClientRole);
    setAutoConnect(true);
}

QDBusObjectPath
SerialPortProfile::objectPath() const
{
    return QDBusObjectPath(QStringLiteral("/SerialPortProfile"));
}

QString
SerialPortProfile::uuid() const
{
    return QStringLiteral("00001101-0000-1000-8000-00805f9b34fb");
}

void
SerialPortProfile::newConnection(BluezQt::DevicePtr device,
                                 const QDBusUnixFileDescriptor &fd,
                                 const QVariantMap &properties,
                                 const BluezQt::Request<> &request)
{
    qDebug() << "Connect" << device->name() << properties;

    m_socket = createSocket(fd);
    if (!m_socket->isValid()) {
        request.cancel();
        return;
    }

    connect(m_socket.data(), &QLocalSocket::readyRead, this, &SerialPortProfile::socketReadyRead);
    connect(
      m_socket.data(), &QLocalSocket::disconnected, this, &SerialPortProfile::socketDisconnected);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SerialPortProfile::writeToSocket);
    //timer->setInterval(1000);
    timer->start(1000);
    //(1000, this, SLOT(writeToSocket()));

    request.accept();
}

void
SerialPortProfile::requestDisconnection(BluezQt::DevicePtr device,
                                        const BluezQt::Request<> &request)
{
    qDebug() << "Disconnect" << device->name();

    request.accept();
}

void
SerialPortProfile::release()
{
    qDebug() << "Release";
}

void SerialPortProfile::socketReadyRead()
{
        qDebug() << "Read:" << m_socket->socketDescriptor() << m_socket->readAll();
}

void SerialPortProfile::socketDisconnected()
{
        qDebug() << "Socket disconnected";
            m_socket.clear();
}

void SerialPortProfile::writeToSocket()
{
        qDebug() << "Writing" << m_socket->socketDescriptor();
            m_socket->write(QByteArrayLiteral("test-data"));
}
