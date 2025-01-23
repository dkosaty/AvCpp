#pragma once

#include "Demuxer.h"
#include "Muxer.h"

#include <atomic>
#include <thread>

namespace AvCpp {
class Remuxer final {
public:
    explicit Remuxer();
    ~Remuxer();

    Remuxer(const Remuxer&) = delete;
    Remuxer& operator=(const Remuxer&) = delete;

    Remuxer(Remuxer&&) noexcept = delete;
    Remuxer& operator=(Remuxer&&) noexcept = delete;

    void Open(const Demuxer::Parameters& demuxerParams,
              const Muxer::Parameters& muxerParams);

    void Close() noexcept;

private:
    void Remux();

private:
    std::shared_ptr<Muxer> _muxer;

    std::shared_ptr<Demuxer> _demuxer;

    std::atomic_bool _isWorking = {false};

    std::thread _thread;
};
} // namespace AvCpp