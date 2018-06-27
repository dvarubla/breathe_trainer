#include "SettingsHelper.h"

namespace breathe_trainer{
    SettingsHelper::SettingsHelper(const ISettingsPtr &settings, const ITrainProfMCopyPtr &profModel)
            : _settings(settings), _profModel(profModel){
    }

    void SettingsHelper::onAppExit() {
        _settings->save(_profModel->profileList(), _profModel->profileMap());
    }
}