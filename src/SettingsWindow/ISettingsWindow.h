#pragma once

#include <memory>

namespace breathe_trainer {
    class ISettingsWindow {
    public:
        virtual void showWindow() = 0;
    };
    typedef std::shared_ptr<ISettingsWindow> ISettWinPtr;
}
