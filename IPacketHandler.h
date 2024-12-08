#pragma once

#include <memory>

struct AVPacket;

namespace AvCpp
{
class IPacketHandler
{
public:
    virtual ~IPacketHandler() = default;

    virtual void Handle(AVPacket*) = 0;
};

using IPacketHandlerPtr = std::shared_ptr<IPacketHandler>;
} // namespace AvCpp