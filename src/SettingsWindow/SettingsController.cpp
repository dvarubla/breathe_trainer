#include <TrainProfiles/ITrainProfilesModelEdit.h>
#include "SettingsController.h"

namespace breathe_trainer{

    SettingsController::SettingsController(
            const ISettWinPtr &settingsWin,
            const ITrainProfMEditPtr &trainProfModel,
            const IProfMUpdaterPtr &profModelUpdater
    ) :
            _settingsWin(settingsWin), _trainProfModel(trainProfModel), _profModelUpdater(profModelUpdater){
    }

    void SettingsController::show() {
        _profModelUpdater->rollback();
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

    void SettingsController::onPositionChanged(int index, const std::string &oldName, const ProfileStrs &profileStrs, const std::string &newName) {
        saveCurrent(index, oldName, profileStrs);
        _settingsWin->setFieldStrings(formProfileStrs(newName, _trainProfModel->getProfileByName(newName)));
    }

    void SettingsController::onSaveBtnClicked() {
        auto profileStrs = _settingsWin->getProfileStrings();
        auto name = _settingsWin->getSelectedProfileName();
        auto index = _settingsWin->getSelectedIndex();
        saveCurrent(index, name, profileStrs);
        _profModelUpdater->commit();
    }

    void SettingsController::saveCurrent(int index, const std::string &name, const ProfileStrs &profileStrs) {
        TrainProfile prof = {
                std::stoul(profileStrs.inhalationTime),
                std::stoul(profileStrs.pauseTimeAfterInhalation),
                std::stoul(profileStrs.exhalationTime),
                std::stoul(profileStrs.pauseTimeAfterExhalation),
        };
        if(name != profileStrs.name){
            _settingsWin->setProfile(index, profileStrs.name);
        }
        _trainProfModel->setProfile(profileStrs.name, prof, name);
    }
}
