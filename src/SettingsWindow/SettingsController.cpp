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
        initWindow();
        _settingsWin->showWindow();
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

    void SettingsController::onCancelBtnClicked() {
        _profModelUpdater->rollback();
        initWindow();
    }

    void SettingsController::initWindow() {
        _settingsWin->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
        std::string firstName = *_trainProfModel->profileNamesBegin();
        _settingsWin->setFieldStrings(formProfileStrs(firstName, _trainProfModel->getProfileByName(firstName)));
    }

    void SettingsController::onMoveUpBtnClicked() {
        auto index = _settingsWin->getSelectedIndex();
        if(_trainProfModel->moveUp(_settingsWin->getSelectedProfileName())){
            initWindow();
            _settingsWin->setSelectedIndex(index - 1);
        }
    }

    void SettingsController::onMoveDownBtnClicked() {
        auto index = _settingsWin->getSelectedIndex();
        if(_trainProfModel->moveDown(_settingsWin->getSelectedProfileName())){
            initWindow();
            _settingsWin->setSelectedIndex(index + 1);
        }
    }

    void SettingsController::onAddBtnClicked() {
        auto res = _settingsWin->showAddNameDialog();
        if(res){
            _trainProfModel->addProfile(*res);
            _settingsWin->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
            _settingsWin->setSelectedIndex(static_cast<int>(_trainProfModel->numProfiles()) - 1);
        }
    }

    void SettingsController::onDeleteBtnClicked() {
        _trainProfModel->deleteProfile(_settingsWin->getSelectedProfileName());
        initWindow();
    }
}
