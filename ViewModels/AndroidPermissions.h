#pragma once

#include <QObject>

class AndroidPermissions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool storagePermission READ storagePermission WRITE setStoragePermission NOTIFY storagePermissionChanged)
    Q_PROPERTY(bool usbPermission READ usbPermission WRITE setUsbPermission NOTIFY usbPermissionChanged)

public:
    explicit AndroidPermissions(QObject *parent = nullptr);

    bool storagePermission() const;
    void setStoragePermission(bool newStoragePermission);

    bool usbPermission() const;
    void setUsbPermission(bool newStoragePermission);

public slots:
    void requestPermissions();

signals:
    void storagePermissionChanged();
    void usbPermissionChanged();

private:
    bool m_storagePermission;
    bool m_usbPermission;
};
