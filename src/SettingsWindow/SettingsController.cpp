#include "SettingsController.h"

namespace breathe_trainer{

    SettingsController::SettingsController(const ISettWinPtr &settingsWin, const ITrainProfMPtr &trainProfModel) :
            _settingsWin(settingsWin), _trainProfModel(trainProfModel){
    }

    void SettingsController::show() {
        _settingsWin->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
        _settingsWin->showWindow();
        _settingsWin->setFieldStrings(formProfileStrs(_trainProfModel->getProfileByName(*_trainProfModel->profileNamesBegin())));
    }

    ProfileStrs SettingsController::formProfileStrs(const TrainProfile &profile) {
        return {
                std::to_string(profile.inhalationTime),
                std::to_string(profile.pauseTimeAfterInhalation),
                std::to_string(profile.exhalationTime),
                std::to_string(profile.pauseTimeAfterExhalation)
        };
    }
}
