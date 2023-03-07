#pragma once

#include <QString>

class DeviceInfo
{
public:
    static DeviceInfo& getInstance()
    {
        static DeviceInfo instance;
        return instance;
    }

    void setValues(QString path, int fd, int pid, int vid);
private:
    DeviceInfo();
    DeviceInfo(DeviceInfo const&) = delete;
    void operator=(DeviceInfo const&)  = delete;

public:
    QString path;
    int fd;
    int pid;
    int vid;
};
