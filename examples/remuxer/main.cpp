#include <Remuxer.h>

#include <atomic>
#include <condition_variable>
#include <csignal>
#include <iostream>
#include <mutex>

namespace {
std::atomic_bool signalIsReceived = {false};
std::condition_variable signalCv;
std::mutex signalMx;
}

int main() {
    std::signal(SIGINT, [](int signal) {
        signalIsReceived = true;
        signalCv.notify_one();
    });

    try {
        AvCpp::Remuxer remuxer;

        remuxer.Open(AvCpp::Demuxer::Parameters{"/mnt/c/share/Camera01/1.mp4"},
                     AvCpp::Muxer::Parameters{"udp://127.0.0.1:5000?pkt_size=1316", "mpegts"});

        std::unique_lock <std::mutex> lock(signalMx);
        signalCv.wait(lock, [] { return static_cast<bool>(signalIsReceived); });

        remuxer.Close();
    }
    catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return -1;
    }

    return 0;
}