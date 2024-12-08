#pragma once

#include "IPacketHandler.h"

#include <string>

struct AVFormatContext;

namespace AvCpp
{
class Muxer
    : public IPacketHandler
{
public:
    struct Parameters
    {
        explicit Parameters(std::string url, std::string formatName = {})
                : url(std::move(url))
                , formatName(std::move(formatName))
        {
        }

        std::string url;
        std::string formatName;
    };

    explicit Muxer();

    ~Muxer() override;

    void Open(const Parameters& parameters);

    void Close() noexcept;

    void Handle(AVPacket* packet) override;

private:
    AVFormatContext* _formatContext = nullptr;
};
} // namespace AvCpp