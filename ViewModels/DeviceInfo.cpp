#include "DeviceInfo.h"

void DeviceInfo::setValues(QString path, int fd, int pid, int vid)
{
    this->path = path;
    this->fd = fd;
    this->vid = vid;
    this->pid = pid;
}

DeviceInfo::DeviceInfo()
{

}
