#pragma once

#include <BluezQt/Profile>

#include <QLocalSocket>
#include <QSharedPointer>

class SerialPortProfile : public BluezQt::Profile
{
    Q_OBJECT

public:
    explicit SerialPortProfile(QObject *parent);

    QDBusObjectPath objectPath() const override;
    QString uuid() const override;

    void newConnection(BluezQt::DevicePtr device,
                       const QDBusUnixFileDescriptor &fd,
                       const QVariantMap &properties,
                       const BluezQt::Request<> &request) override;

    void
    requestDisconnection(BluezQt::DevicePtr device, const BluezQt::Request<> &request) override;
    void release() override;

private Q_SLOTS:
    void socketReadyRead();
    void socketDisconnected();
    void writeToSocket();

private:
    QSharedPointer<QLocalSocket> m_socket;
};
