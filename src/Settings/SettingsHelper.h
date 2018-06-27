#pragma once

#include <TrainProfiles/ITrainProfilesModelCopy.h>
#include "ISettingsListener.h"
#include "ISettings.h"
#include "IWindowSettingsModel.h"

namespace breathe_trainer {
    class SettingsHelper: public ISettingsListener {
    private:
        ISettingsPtr _settings;
        ITrainProfMCopyPtr _profModel;
        IWinSettMPtr _settWinModel;
    public:
        SettingsHelper(const ISettingsPtr &settings, const ITrainProfMCopyPtr &profModel, const IWinSettMPtr &settWinModel);

        void onAppExit() override;
    };
}
