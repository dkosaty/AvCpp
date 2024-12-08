#include "Remuxer.h"

extern "C"
{
#include <libavcodec/packet.h>
}

namespace AvCpp
{
Remuxer::Remuxer()
    : _isWorking(true)
    , _thread(&Remuxer::Remux, this)
{
    _muxer = std::make_shared<Muxer>();
    _demuxer = std::make_shared<Demuxer>(_muxer);
}

Remuxer::~Remuxer()
{
    _isWorking = false;

    if (_thread.joinable())
        _thread.join();
}

void Remuxer::Open(const Demuxer::Parameters& demuxerParams,
                   const Muxer::Parameters& muxerParams)
{
    _demuxer->Open(demuxerParams);
    _muxer->Open(muxerParams);
}

void Remuxer::Close() noexcept
{
    _muxer->Close();
    _demuxer->Close();
}

void Remuxer::Remux()
{
    while (!_isWorking)
    {
        AVPacket packet;
        if (_demuxer != nullptr)
            _demuxer->Handle(&packet);
    }
}
} // namespace AvCpp