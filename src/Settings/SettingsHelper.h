#pragma once

#include <TrainProfiles/ITrainProfilesModelCopy.h>
#include "ISettingsListener.h"
#include "ISettings.h"

namespace breathe_trainer {
    class SettingsHelper: public ISettingsListener {
    private:
        ISettingsPtr _settings;
        ITrainProfMCopyPtr _profModel;
    public:
        SettingsHelper(const ISettingsPtr &settings, const ITrainProfMCopyPtr &profModel);

        void onAppExit() override;
    };
}
