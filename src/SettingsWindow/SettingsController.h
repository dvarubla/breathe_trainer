#pragma once

#include "ISettingsWindow.h"
#include "ISettingsController.h"

namespace breathe_trainer {
    class SettingsController: public ISettingsController {
    private:
        ISettWinPtr _settingsWin;
    public:
        explicit SettingsController(const ISettWinPtr &settingsWin);

        void show() override;
    };
}
