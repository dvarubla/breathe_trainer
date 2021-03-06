#include <TrainProfiles/ITrainProfilesModelEdit.h>
#include "SettingsController.h"

namespace breathe_trainer{
    SettingsController::SettingsController(
            const ISettWinPtr &settingsWin,
            const ITrainProfMEditPtr &trainProfModel,
            const IProfMUpdaterPtr &profModelUpdater,
            const IWinSettMPtr &winSettModel
    ) :
            _settingsWin(settingsWin), _trainProfModel(trainProfModel), _profModelUpdater(profModelUpdater), _winSettModel(winSettModel){
        auto size = winSettModel->getSize(SETTINGS_WINDOW_NAME);
        _settingsWin->resize(size.width, size.height);
    }

    void SettingsController::show() {
        _profModelUpdater->rollback();
        initWindow();
        _settingsWin->showWindow();
    }

    ProfileData SettingsController::formProfileData(const std::string &name, const TrainProfile &profile) {
        return {
                name,
                profile
        };
    }

    void SettingsController::onPositionChanged(int index, const std::string &oldName, const ProfileData &profileData, const std::string &newName) {
        bool saved = saveCurrent(index, oldName, profileData);
        if(!saved){
            ProfileData editedData = profileData;
            editedData.name = oldName;
            saveCurrent(index, oldName, editedData);
        }
        _settingsWin->setFieldStrings(formProfileData(newName, _trainProfModel->getProfileByName(newName)));
        setUpDownButtons();
        if(!saved){
            _settingsWin->showAddErrDialog(profileData.name);
        }
    }

    void SettingsController::onSaveBtnClicked() {
        if(_trainProfModel->numProfiles() != 0) {
            auto profileData = _settingsWin->getProfileStrings();
            auto name = _settingsWin->getSelectedProfileName();
            auto index = _settingsWin->getSelectedIndex();
            if(!saveCurrent(index, name, profileData)){
                _settingsWin->showAddErrDialog(profileData.name);
                return;
            }
        }
        _profModelUpdater->commit();
    }

    bool SettingsController::saveCurrent(int index, const std::string &name, const ProfileData &profileData) {
        TrainProfile prof = profileData.profile;
        if(!_trainProfModel->setProfile(profileData.name, prof, name)){
            return false;
        }
        if(name != profileData.name){
            _settingsWin->setProfile(index, profileData.name);
        }
        return true;
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
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_UP, true);
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_DOWN,
                                                _trainProfModel->numProfiles() == 1);
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
            if(!_trainProfModel->addProfile(*res)){
                _settingsWin->showAddErrDialog(*res);
                return;
            }
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

    void SettingsController::onResize(uint_fast32_t w, uint_fast32_t h) {
        _winSettModel->saveSize(SETTINGS_WINDOW_NAME, {w, h});
    }

    void SettingsController::onCommit() {
        initWindow();
    }
}
