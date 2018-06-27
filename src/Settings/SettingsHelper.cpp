#include "SettingsHelper.h"

namespace breathe_trainer{
    SettingsHelper::SettingsHelper(
            const ISettingsPtr &settings,
            const ITrainProfMCopyPtr &profModel,
            const IWinSettMPtr &settWinModel
    )
            : _settings(settings), _profModel(profModel), _settWinModel(settWinModel){
    }

    void SettingsHelper::onAppExit() {
        _settings->saveProfiles(_profModel->profileList(), _profModel->profileMap());
        _settings->saveWindowData(_settWinModel->getData());
    }
}