// include/model/Schedulable.h
#pragma once

namespace model {

/// Interfaz Schedulable: permite asociar un calendario mediante su ID
class Schedulable {
public:
    /// Obtiene el ID de calendario asociado
    virtual long getCalendarId() const = 0;

    /// Asigna el ID de calendario asociado
    virtual void setCalendarId(long calendarId) = 0;

    virtual ~Schedulable() = default;
};

} // namespace model
