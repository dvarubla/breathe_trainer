#pragma once

#include <TrainProfiles/ITrainProfilesModel.h>
#include "ISettingsWindow.h"
#include "ISettingsController.h"

namespace breathe_trainer {
    class SettingsController: public ISettingsController {
    private:
        ISettWinPtr _settingsWin;
        ITrainProfMEditPtr _trainProfModel;
        ProfileStrs formProfileStrs(const std::string &name, const TrainProfile &profile);
    public:
        explicit SettingsController(const ISettWinPtr &settingsWin, const ITrainProfMEditPtr &trainProfModel);

    private:
        void onPositionChanged(int index, const std::string &oldName, const ProfileStrs &profileStrs, const std::string &newName) override;

    public:

        void show() override;
    };
}
