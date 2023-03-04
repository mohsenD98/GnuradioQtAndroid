#include "AndroidPermissions.h"

#include <QDebug>
#include <QtCore/private/qandroidextras_p.h>

bool checkAppPermissions(QString permission)
{
    auto result = QtAndroidPrivate::checkPermission(permission).result();
    qDebug() << "--------------------" << permission << result << QtAndroidPrivate::Denied;
    if (result == QtAndroidPrivate::Denied) {
        auto result2 = QtAndroidPrivate::requestPermission(permission).result();
        qDebug() << permission << result2;

        if (result2 == QtAndroidPrivate::Denied)
            return false;

        else {
            /* Here is Your method to upload to storage */

            return true;
        }
    }

    else {
        /* Here is Your method to upload to storage */

        return true;
    }
}

AndroidPermissions::AndroidPermissions(QObject *parent)
    : QObject{parent}
{
    setUsbPermission(true);
    setStoragePermission(false);

    requestPermissions();
}

void AndroidPermissions::requestPermissions()
{
    qDebug() << "requesting Permissions...";
    setStoragePermission(checkAppPermissions("android.permission.WRITE_EXTERNAL_STORAGE") && checkAppPermissions("android.permission.READ_EXTERNAL_STORAGE"));
//    setUsbPermission(checkAppPermissions("com.android.example.USB_PERMISSION"));
}

bool AndroidPermissions::storagePermission() const
{
    return m_storagePermission;
}

void AndroidPermissions::setStoragePermission(bool newStoragePermission)
{
    if (m_storagePermission == newStoragePermission)
        return;
    m_storagePermission = newStoragePermission;
    emit storagePermissionChanged();
}

bool AndroidPermissions::usbPermission() const
{
    return m_usbPermission;
}

void AndroidPermissions::setUsbPermission(bool newUsbPermission)
{
    if (m_usbPermission == newUsbPermission)
        return;
    m_usbPermission = newUsbPermission;
    emit usbPermissionChanged();
}
