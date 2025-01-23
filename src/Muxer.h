#pragma once

#include "IPacketHandler.h"

#include <string>
#include <string_view>

struct AVFormatContext;

namespace AvCpp {
class Muxer
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

    explicit Muxer();
    ~Muxer() override;

    Muxer(const Muxer&) = delete;
    Muxer& operator=(const Muxer&) = delete;

    Muxer(Muxer&&) noexcept = delete;
    Muxer& operator=(Muxer&&) noexcept = delete;

    void Open(const Parameters& parameters);

    void Close() noexcept;

    void Handle(AVPacket* packet) override;

private:
    AVFormatContext* _formatContext = nullptr;
};
} // namespace AvCpp