#include "SettingsController.h"

namespace breathe_trainer{

    SettingsController::SettingsController(const ISettWinPtr &settingsWin, const ITrainProfMPtr &trainProfModel) :
            _settingsWin(settingsWin), _trainProfModel(trainProfModel){
    }

    void SettingsController::show() {
        _settingsWin->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
        _settingsWin->showWindow();
        std::string firstName = *_trainProfModel->profileNamesBegin();
        _settingsWin->setFieldStrings(formProfileStrs(firstName, _trainProfModel->getProfileByName(firstName)));
    }

    ProfileStrs SettingsController::formProfileStrs(const std::string &name, const TrainProfile &profile) {
        return {
                name,
                std::to_string(profile.inhalationTime),
                std::to_string(profile.pauseTimeAfterInhalation),
                std::to_string(profile.exhalationTime),
                std::to_string(profile.pauseTimeAfterExhalation)
        };
    }

    void SettingsController::onPositionChanged(const std::string &str) {
        _settingsWin->setFieldStrings(formProfileStrs(str, _trainProfModel->getProfileByName(str)));
    }
}
