#include "Demuxer.h"
#include "Utils.h"

extern "C" {
#include <libavformat/avformat.h>
}

#include <stdexcept>

namespace AvCpp {
Demuxer::Demuxer(IPacketHandlerPtr handler)
    : _handler(std::move(handler))
    , _formatContext(avformat_alloc_context()) {
}

Demuxer::~Demuxer() {
    avformat_free_context(_formatContext);
}

void Demuxer::Open(const Parameters& parameters) {
    const AVInputFormat* format = av_find_input_format(parameters.formatName.c_str());

    int errorCode;
    if ((errorCode = avformat_open_input(&_formatContext, parameters.url.c_str(), format, nullptr)) < 0)
        throw std::runtime_error("Can't open input: " + av_err2str(errorCode));

    if ((errorCode = avformat_find_stream_info(_formatContext, nullptr)) < 0)
        throw std::runtime_error("Can't find stream info: " + av_err2str(errorCode));

    for (int i = 0; i < _formatContext->nb_streams; ++i)
        av_dump_format(_formatContext, i, parameters.url.c_str(), 0);
}

void Demuxer::Close() noexcept {
    if (_formatContext != nullptr)
        avformat_close_input(&_formatContext);
}

void Demuxer::Handle(AVPacket* packet) {
    int errorCode;
    if ((errorCode = av_read_frame(_formatContext, packet)) < 0)
        throw std::runtime_error("Can't read frame: " + av_err2str(errorCode));

    _handler->Handle(packet);
}
} // namespace AvCpp