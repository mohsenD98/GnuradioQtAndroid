#include "GFlow.h"

#include <QDebug>
#include <QStandardPaths>
#include <qdir.h>

#include "DeviceInfo.h"
#include "AndroidLogger.h"

GFlow::GFlow(QObject *parent)
    : QObject{parent}
{

}

void GFlow::initial()
{
    setenv("VOLK_CONFIGPATH", getenv("EXTERNAL_STORAGE"), 1);
    setenv("GR_CONF_CONTROLPORT_ON", "true", 1);

    tb = gr::make_top_block("fg");

    ss << "hackrf=0,fd=" << DeviceInfo::getInstance().fd << ",usbfs=" << DeviceInfo::getInstance().path.toStdString();

    GR_INFO("gnuradio", ss.str());

    src = osmosdr::source::make(ss.str());
    src->set_sample_rate(2e6);
    src->set_center_freq(96.8e6);
    src->set_gain(0, "RF", 0);
    src->set_gain(24, "IF", 0);
    src->set_gain(20, "BB", 0);

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/mgnuradioandroitest1";
    if (!writeDir.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    QString folder=QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QFile* file=new QFile(folder+"/test.txt");
    if (!file->exists()) {
        // create the folder, if necessary
        QDir* dir=new QDir(folder);
        if (!dir->exists()) {
            AndroidLogger::sendAdbLog("creating new folder");
            dir->mkpath(".");
        }
        AndroidLogger::sendAdbLog("creating new file");
        file->open(QIODevice::WriteOnly);
        file->write("Hello World");
        file->close();
    }
    if (file->exists()) {
        AndroidLogger::sendAdbLog("file exists");
        file->open(QIODevice::ReadOnly);
        QByteArray data=file->readAll();
        file->close();
    }

    AndroidLogger::sendAdbLog("selected file is this: "+(folder+"/test.sig"));


    file_sink= gr::blocks::file_sink::make(sizeof(char), (folder+"/test.sig").toStdString().c_str(), false);

}

void GFlow::connect()
{
    tb->connect(src, 0, file_sink, 0);
}

void GFlow::start()
{
    tb->start();
}

void GFlow::stop()
{
    tb->wait();
    tb->stop();
}



