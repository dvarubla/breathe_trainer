#include "SettingsController.h"

namespace breathe_trainer{

    SettingsController::SettingsController(const ISettWinPtr &settingsWin) : _settingsWin(settingsWin) {
    }

    void SettingsController::show() {
        _settingsWin->showWindow();
    }
}
