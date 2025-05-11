// include/model/BaseCommand.h
#pragma once

#include "model/Message.h"

namespace model {

/// BaseCommand: comando base que extiende Message y puede usar canal de texto
class BaseCommand : public Message {
public:
    /// Indica si el comando debe enviarse por canal de texto
    bool getTextChannel() const noexcept { return textChannel_; }

    /// Define si el comando irá por canal de texto
    void setTextChannel(bool textChannel) noexcept { textChannel_ = textChannel; }

private:
    bool textChannel_{false};
};

} // namespace model
