#include "AndroidPermissions.h"

#include <QDebug>
#include <QCoreApplication>
#include <jni.h>
#include <QDebug>

#include "AndroidLogger.h"
#include "DeviceInfo.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
  Java_org_qtproject_example_HandlePermissions_sendParamsToCpp(JNIEnv *env,
                                                    jobject obj,
                                                    jstring path, jint fd, jint v, jint p)
{

    AndroidLogger::sendAdbLog("ok back from java!");
    QString mpath(env->GetStringUTFChars(path, 0));
    int vId = (int) v;
    int pId = (int) p;
    int mFd = (int) fd;
    AndroidLogger::sendAdbLog("path: "+ mpath + "\nVID:" + QString::number(vId) + "\npID:" + QString::number(pId) + "\nfd: " + QString::number(mFd));
    DeviceInfo::getInstance().setValues(mpath, mFd, pId, vId);
    AndroidPermissions::getInstance().setStoragePermission(true);
    AndroidPermissions::getInstance().setUsbPermission(true);
}


#ifdef __cplusplus
}
#endif

void AndroidPermissions::requestPermissions()
{
    QJniObject javaMessage = QJniObject::fromString("mohsenmessage");

    QJniEnvironment env;
    jclass javaClass = env.findClass("org/qtproject/example/HandlePermissions");
    QJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 activity.object<jobject>());

    QJniObject::callStaticMethod<void>("org/qtproject/example/HandlePermissions",
                                       "checkStoragePermission",
                                       "(Landroid/app/Activity;Ljava/lang/String;)V",
                                       activity.object<jobject>(), javaMessage.object<jstring>());
}

AndroidPermissions::AndroidPermissions()
{
    setUsbPermission(false);
    setStoragePermission(false);

#ifdef Q_OS_ANDROID
    activity = QJniObject(QNativeInterface::QAndroidApplication::context());
#endif

}

bool AndroidPermissions::storagePermission()
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

bool AndroidPermissions::usbPermission()
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
