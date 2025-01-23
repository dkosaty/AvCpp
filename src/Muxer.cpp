#include "Muxer.h"
#include "Utils.h"

extern "C" {
#include <libavformat/avformat.h>
}

#include <iostream>

namespace AvCpp {
Muxer::Muxer()
    : _formatContext(avformat_alloc_context()) {
}

Muxer::~Muxer() {
    avformat_free_context(_formatContext);
}

void Muxer::Open(const Parameters& parameters) {
    _formatContext->oformat = av_guess_format(parameters.formatName.c_str(), nullptr, nullptr);
    if (_formatContext->oformat == nullptr)
        throw std::runtime_error("Can't guess output format");

    const AVStream* outputStream = avformat_new_stream(_formatContext, nullptr);
    if (outputStream == nullptr)
        throw std::runtime_error("Can't create output stream");

    int errorCode;
//    errorCode = avcodec_parameters_copy(outputStream->codecpar, inputStream->codecpar);

    if ((errorCode = avio_open(&_formatContext->pb, parameters.url.c_str(), AVIO_FLAG_WRITE)) < 0)
        throw std::runtime_error("Can't open output: " + av_err2str(errorCode));

//    if ((errorCode = avformat_write_header(_formatContext, nullptr)) < 0)
//        throw std::runtime_error("Can't write header: " + av_err2str(errorCode));

    for (int i = 0; i < _formatContext->nb_streams; ++i)
        av_dump_format(_formatContext, i, parameters.url.c_str(), 1);
}

void Muxer::Close() noexcept {
    if (_formatContext != nullptr && _formatContext->pb != nullptr)
        avio_closep(&_formatContext->pb);

    int errorCode;
    if ((errorCode = av_write_trailer(_formatContext)) < 0)
        std::cerr << ":" << av_err2str(errorCode) << std::endl;
}

void Muxer::Handle(AVPacket* packet) {
    if (packet == nullptr)
        throw std::runtime_error("Invalid packet");

//    av_packet_rescale_ts(&packet, inputStream->time_base, outputStream->time_base)

    int errorCode;
    if ((errorCode = av_interleaved_write_frame(_formatContext, packet)) < 0)
        std::cerr << "Can't write frame:" << av_err2str(errorCode) << std::endl;
}
} // namespace AvCpp