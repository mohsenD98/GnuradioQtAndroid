#include "GFlow.h"

#include <QDebug>
#include <QStandardPaths>

GFlow::GFlow(QObject *parent)
    : QObject{parent}
{

}

void GFlow::initial()
{
    setenv("VOLK_CONFIGPATH", getenv("EXTERNAL_STORAGE"), 1);
    setenv("GR_CONF_CONTROLPORT_ON", "true", 1);
    float samp_rate = 320e3;
    std::vector<float> chan_taps = gr::filter::firdes::low_pass_2(1, samp_rate, 150e3, 50e3, 60,
                                                                  gr::filter::firdes::WIN_HANN);
    int resamp = 10;
    std::vector<float> audio_taps = gr::filter::firdes::low_pass_2(6, samp_rate, 10e3, 2e3, 60,
                                                                   gr::filter::firdes::WIN_HANN);
    float max_dev = 75e3;
    float fm_demod_gain = static_cast<float>(samp_rate / (2.0f * M_PI * max_dev*15));
    float audio_rate = samp_rate / resamp;
    tb = gr::make_top_block("fg");

    // FD is not a correct number right now!! should be corrected!
    ss << "hackrf=0,fd=" << fd() << ",usbfs=" << usbPath().toStdString();

    GR_INFO("gnuradio", ss.str());

//    src = osmosdr::source::make(ss.str());
//    src->set_sample_rate(2e6);
//    src->set_center_freq(96.8e6);
//    src->set_gain(0, "RF", 0);
//    src->set_gain(24, "IF", 0);
//    src->set_gain(20, "BB", 0);

    file_source = gr::blocks::file_source::make(sizeof(char), "/storage/emulated/0/Download/fan2016.pdf", false);
    xlat = gr::filter::freq_xlating_fir_filter_ccf::make(1, {1}, -.5e6, 2e6);

//    arb = gr::filter::pfb_arb_resampler_ccf::make(324e3/2e6, {}, 32);
//    arb->declare_sample_delay(0);

    chan_filt = gr::filter::fir_filter_ccf::make(1, chan_taps);
    demod = gr::analog::quadrature_demod_cf::make(fm_demod_gain);
    audio_filt = gr::filter::fir_filter_fff::make(resamp, audio_taps);
//    probe = gr::fft::ctrlport_probe_psd::make("probe", "foo", 1024);
    snk = gr::grand::opensl_sink::make(int(audio_rate));

    qDebug() << "init done!";
}

void GFlow::connect()
{
    tb->connect(src, 0, xlat, 0);
    tb->connect(xlat, 0, arb, 0);
    tb->connect(xlat, 0, probe, 0);
    tb->connect(arb, 0, chan_filt, 0);
    tb->connect(chan_filt, 0, demod, 0);
    tb->connect(demod, 0, audio_filt, 0);
    tb->connect(audio_filt, 0, snk, 0);

    qDebug() << "connect done!";
}

const QString &GFlow::usbPath() const
{
    return m_usbPath;
}

void GFlow::setUsbPath(const QString &newUsbPath)
{
    if (m_usbPath == newUsbPath)
        return;
    m_usbPath = newUsbPath;
    emit usbPathChanged();
}

int GFlow::fd() const
{
    return m_fd;
}

void GFlow::setFd(int newFd)
{
    if (m_fd == newFd)
        return;
    m_fd = newFd;
    emit fdChanged();
}
