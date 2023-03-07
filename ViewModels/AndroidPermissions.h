#pragma once

#include <QObject>

#ifdef Q_OS_ANDROID
#include <QJniEnvironment>
#include <QtCore/private/qandroidextras_p.h>
#include <QJniObject>
#endif

class AndroidPermissions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool storagePermission READ storagePermission WRITE setStoragePermission NOTIFY storagePermissionChanged)
    Q_PROPERTY(bool usbPermission READ usbPermission WRITE setUsbPermission NOTIFY usbPermissionChanged)

public:
    static AndroidPermissions& getInstance()
    {
        static AndroidPermissions instance;
        return instance;
    }

    bool storagePermission();
    void setStoragePermission(bool newStoragePermission);

    bool usbPermission() ;
    void setUsbPermission(bool newStoragePermission);

public slots:
    void requestPermissions();

signals:
    void storagePermissionChanged();
    void usbPermissionChanged();

private:
    AndroidPermissions();
    AndroidPermissions(AndroidPermissions const&) = delete;
    void operator=(AndroidPermissions const&)  = delete;

private:
    bool m_storagePermission;
    bool m_usbPermission;

#ifdef Q_OS_ANDROID
    QJniEnvironment _env;
    QJniObject  activity;
#endif

};
