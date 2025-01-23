#pragma once

#include "IPacketHandler.h"

#include <string>
#include <string_view>
#include <utility>

struct AVFormatContext;

namespace AvCpp {
class Demuxer
    : public IPacketHandler {
public:
    struct Parameters {
        explicit Parameters(std::string_view url, std::string_view formatName = {})
            : url(url)
            , formatName(formatName) {
        }

        std::string url;
        std::string formatName;
    };

    explicit Demuxer(IPacketHandlerPtr handler);
    ~Demuxer() override;

    Demuxer(const Demuxer&) = delete;
    Demuxer& operator=(const Demuxer&) = delete;

    Demuxer(Demuxer&&) noexcept = delete;
    Demuxer& operator=(Demuxer&&) noexcept = delete;

    void Open(const Parameters& parameters);

    void Close() noexcept;

    void Handle(AVPacket* packet) override;

private:
    IPacketHandlerPtr _handler;

    AVFormatContext* _formatContext = nullptr;
};
} // namespace AvCpp