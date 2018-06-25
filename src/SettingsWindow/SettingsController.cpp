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

    ProfileData SettingsController::formProfileData(const std::string &name, const TrainProfile &profile) {
        return {
                name,
                profile.inhalationTime,
                profile.pauseTimeAfterInhalation,
                profile.exhalationTime,
                profile.pauseTimeAfterExhalation
        };
    }

    void SettingsController::onPositionChanged(int index, const std::string &oldName, const ProfileData &profileData, const std::string &newName) {
        saveCurrent(index, oldName, profileData);
        _settingsWin->setFieldStrings(formProfileData(newName, _trainProfModel->getProfileByName(newName)));
        setUpDownButtons();
    }

    void SettingsController::onSaveBtnClicked() {
        if(_trainProfModel->numProfiles() != 0) {
            auto profileData = _settingsWin->getProfileStrings();
            auto name = _settingsWin->getSelectedProfileName();
            auto index = _settingsWin->getSelectedIndex();
            saveCurrent(index, name, profileData);
        }
        _profModelUpdater->commit();
    }

    void SettingsController::saveCurrent(int index, const std::string &name, const ProfileData &profileData) {
        TrainProfile prof = {
                profileData.inhalationTime,
                profileData.pauseTimeAfterInhalation,
                profileData.exhalationTime,
                profileData.pauseTimeAfterExhalation,
        };
        if(name != profileData.name){
            _settingsWin->setProfile(index, profileData.name);
        }
        _trainProfModel->setProfile(profileData.name, prof, name);
    }

    void SettingsController::onCancelBtnClicked() {
        _profModelUpdater->rollback();
        initWindow();
    }

    void SettingsController::initWindow() {
        if(_trainProfModel->numProfiles() == 0){
            _settingsWin->clearProfiles();
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::DELETE, true);
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_UP, true);
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_DOWN, true);
        } else {
            _settingsWin->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
            std::string firstName = *_trainProfModel->profileNamesBegin();
            _settingsWin->setFieldStrings(formProfileData(firstName, _trainProfModel->getProfileByName(firstName)));
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::DELETE, false);
            if(_trainProfModel->numProfiles() != 1) {
                _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_UP, false);
                _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_DOWN, false);
            } else {
                _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_UP, true);
                _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_DOWN, true);
            }
        }
    }

    void SettingsController::onMoveUpBtnClicked() {
        auto index = _settingsWin->getSelectedIndex();
        if(_trainProfModel->moveUp(_settingsWin->getSelectedProfileName())){
            initWindow();
            _settingsWin->setSelectedIndex(index - 1);
            setUpDownButtons();
        }
    }

    void SettingsController::onMoveDownBtnClicked() {
        auto index = _settingsWin->getSelectedIndex();
        if(_trainProfModel->moveDown(_settingsWin->getSelectedProfileName())){
            initWindow();
            _settingsWin->setSelectedIndex(index + 1);
            setUpDownButtons();
        }
    }

    void SettingsController::onAddBtnClicked() {
        auto res = _settingsWin->showAddNameDialog();
        if(res){
            _trainProfModel->addProfile(*res);
            initWindow();
            _settingsWin->setSelectedIndex(static_cast<int>(_trainProfModel->numProfiles()) - 1);
        }
    }

    void SettingsController::onDeleteBtnClicked() {
        _trainProfModel->deleteProfile(_settingsWin->getSelectedProfileName());
        initWindow();
    }

    void SettingsController::setUpDownButtons() {
        _settingsWin->setButtonDisabled(
                ISettingsWindow::ButtonId::MOVE_UP, _settingsWin->getSelectedIndex() == 0
        );
        _settingsWin->setButtonDisabled(
                ISettingsWindow::ButtonId::MOVE_DOWN,
                static_cast<uint_fast32_t>(_settingsWin->getSelectedIndex()) == _trainProfModel->numProfiles() - 1
        );
    }
}
