#pragma once

#include <QObject>
#include <iostream>

#ifdef Q_OS_ANDROID
#include <QJniEnvironment>
#include <QtCore/private/qandroidextras_p.h>
#include <QJniObject>
#endif

class AndroidLogger : public QObject
{
    Q_OBJECT

public:
    static void sendAdbLog(QString msg){

        QJniObject javaMessage = QJniObject::fromString(msg);
        QJniObject::callStaticMethod<void>("org/qtproject/example/JniMessenger",
                                           "Logger",
                                           "(Ljava/lang/String;)V",
                                            javaMessage.object<jstring>());
    }

};
