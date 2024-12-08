#pragma once

#include "IPacketHandler.h"

#include <string>
#include <utility>

struct AVFormatContext;

namespace AvCpp
{
class Demuxer
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

    explicit Demuxer(IPacketHandlerPtr handler);

    ~Demuxer() override;

    void Open(const Parameters& parameters);

    void Close() noexcept;

    void Handle(AVPacket* packet) override;

private:
    IPacketHandlerPtr _handler;

    AVFormatContext* _formatContext = nullptr;
};
} // namespace AvCpp