#include "SettingsController.h"

namespace breathe_trainer{

    SettingsController::SettingsController(const ISettWinPtr &settingsWin, const ITrainProfMPtr &trainProfModel) :
            _settingsWin(settingsWin), _trainProfModel(trainProfModel){
    }

    void SettingsController::show() {
        _settingsWin->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
        _settingsWin->showWindow();
    }
}
