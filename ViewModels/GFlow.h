#pragma once

#include <QObject>
// Get any GNU Radio headers
#include <gnuradio/constants.h>
#include <gnuradio/prefs.h>
#include <gnuradio/sys_paths.h>
#include <gnuradio/logger.h>
#include <gnuradio/top_block.h>
#include <gnuradio/blocks/file_sink.h>
#include <gnuradio/blocks/ctrlport_probe2_f.h>
#include <libhackrf/hackrf.h>
#include <gnuradio/analog/sig_source.h>
#include <osmosdr/source.h>
#include <stdlib.h>


class GFlow : public QObject
{
    Q_OBJECT

public:
    explicit GFlow(QObject *parent = nullptr);

public slots:
    void initial();
    void connect();
    void start();
    void stop();

private:
    gr::top_block_sptr tb;
    osmosdr::source::sptr src;
    std::stringstream ss;
    gr::blocks::file_sink::sptr file_sink;

};
