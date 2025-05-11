// include/TrackerConnector.h
#pragma once

#include "LifecycleObject.h"
#include "protocol/ChannelGroup.h"

namespace protocol {

/// Equivalente al interface Java TrackerConnector
class TrackerConnector : public LifecycleObject {
public:
    virtual ~TrackerConnector() = default;

    /// true si usa UDP (datagram), false si es TCP (stream)
    virtual bool isDatagram() const = 0;

    /// true si lleva SSL/TLS, false otherwise
    virtual bool isSecure() const = 0;

    /// Grupo de canales/sockets gestionados por este conector
    virtual ChannelGroup& getChannelGroup() = 0;
};

} // namespace protocol
