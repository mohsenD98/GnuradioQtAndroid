#include "GFlow.h"

#include <QDebug>
#include <QStandardPaths>
#include <qdir.h>
#include <iostream>
#include <complex.h>

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

    QString folder=QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    file_sink = gr::blocks::file_sink::make(sizeof(std::complex<float>), (folder+"/test.sig").toStdString().c_str(), false);
    AndroidLogger::sendAdbLog("selected file is this: "+(folder+"/test.sig"));
    AndroidLogger::sendAdbLog("initialization finished");
}

void GFlow::connect()
{
    tb->connect(src, 0, file_sink, 0);
    AndroidLogger::sendAdbLog("connection finished");
}

void GFlow::start()
{
    tb->start();
    AndroidLogger::sendAdbLog("started");
}

void GFlow::stop()
{
    tb->stop();
    tb->wait();
    AndroidLogger::sendAdbLog("stoped");
}



