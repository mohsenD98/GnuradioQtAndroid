#ifndef GFLOW_H
#define GFLOW_H

#include <QObject>
// Get any GNU Radio headers
#include <gnuradio/constants.h>
#include <gnuradio/prefs.h>
#include <gnuradio/sys_paths.h>
#include <gnuradio/logger.h>
#include <gnuradio/top_block.h>
#include <gnuradio/blocks/null_source.h>
#include <gnuradio/blocks/throttle.h>
#include <gnuradio/blocks/null_sink.h>
#include <gnuradio/blocks/file_source.h>>
#include <gnuradio/blocks/ctrlport_probe2_f.h>
#include <gnuradio/fft/ctrlport_probe_psd.h>
#include <gnuradio/blocks/float_to_complex.h>
//#include <gnuradio/uhd/usrp_source.h>
#include <libhackrf/hackrf.h>
#include <gnuradio/analog/sig_source.h>
#include <osmosdr/source.h>
#include <grand/opensl_sink.h>

#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/fir_filter_blk.h>
#include <gnuradio/analog/quadrature_demod_cf.h>
#include <gnuradio/analog/fastnoise_source.h>
#include <gnuradio/blocks/ctrlport_probe2_f.h>
#include <gnuradio/filter/pfb_arb_resampler_ccf.h>
#include <gnuradio/filter/freq_xlating_fir_filter.h>
#include <stdlib.h>


class GFlow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString usbPath READ usbPath WRITE setUsbPath NOTIFY usbPathChanged)
    Q_PROPERTY(int fd READ fd WRITE setFd NOTIFY fdChanged)

public:
    explicit GFlow(QObject *parent = nullptr);


    const QString &usbPath() const;
    void setUsbPath(const QString &newUsbPath);

    int fd() const;
    void setFd(int newFd);

public slots:
    void initial();
    void connect();
    QString testing(){return "mohsen";};
signals:
    void usbPathChanged();

    void fdChanged();

private:
    gr::top_block_sptr tb;
    osmosdr::source::sptr src;
    std::stringstream ss;
    std::vector<float> taps{ -7.33845766376362e-08, -7.020744874353113e-08, -6.705249688820913e-08 };

    // Declare our GNU Radio blocks
    gr::filter::freq_xlating_fir_filter_ccf::sptr xlat;
    gr::filter::pfb_arb_resampler_ccf::sptr arb;
    gr::filter::fir_filter_ccf::sptr chan_filt;
    gr::filter::fir_filter_fff::sptr audio_filt;
    gr::analog::quadrature_demod_cf::sptr demod;
    gr::fft::ctrlport_probe_psd::sptr probe;
    gr::blocks::ctrlport_probe2_f::sptr vsnk;
    gr::blocks::file_source::sptr file_source;
    gr::grand::opensl_sink::sptr snk;

    // gui property's
    QString m_usbPath;
    int m_fd;
};

#endif // GFLOW_H
