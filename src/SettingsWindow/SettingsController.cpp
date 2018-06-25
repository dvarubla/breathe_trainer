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
        setUpDownButtons();
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
        if(_trainProfModel->numProfiles() == 0){
            _settingsWin->clearProfiles();
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::DELETE, true);
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_UP, true);
            _settingsWin->setButtonDisabled(ISettingsWindow::ButtonId::MOVE_DOWN, true);
        } else {
            _settingsWin->addProfiles(_trainProfModel->profileNamesBegin(), _trainProfModel->profileNamesEnd());
            std::string firstName = *_trainProfModel->profileNamesBegin();
            _settingsWin->setFieldStrings(formProfileStrs(firstName, _trainProfModel->getProfileByName(firstName)));
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
