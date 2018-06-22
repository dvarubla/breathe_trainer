#pragma once

#include <TrainProfiles/ITrainProfilesModel.h>
#include "ISettingsWindow.h"
#include "ISettingsController.h"

namespace breathe_trainer {
    class SettingsController: public ISettingsController {
    private:
        ISettWinPtr _settingsWin;
        ITrainProfMPtr _trainProfModel;
        ProfileStrs formProfileStrs(const std::string &name, const TrainProfile &profile);
    public:
        explicit SettingsController(const ISettWinPtr &settingsWin, const ITrainProfMPtr &trainProfModel);

    private:
        void onPositionChanged(const std::string &str) override;

    public:

        void show() override;
    };
}
