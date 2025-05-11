// include/LifecycleObject.h
#pragma once

namespace protocol {

/// Contrato de ciclo de vida (start/stop)
class LifecycleObject {
public:
    virtual ~LifecycleObject() = default;
    /// Arranca el servicio (bind/connect, etc.)
    virtual void start() = 0;
    /// Detiene el servicio (cierra sockets, cancela timers…)
    virtual void stop() = 0;
};

} // namespace protocol
