#pragma once

#include <TrainProfiles/ITrainProfilesModel.h>
#include <TrainProfiles/IProfileModelsUpdater.h>
#include "ISettingsWindow.h"
#include "ISettingsController.h"

namespace breathe_trainer {
    class SettingsController: public ISettingsController {
    private:
        ISettWinPtr _settingsWin;
        ITrainProfMEditPtr _trainProfModel;
        IProfMUpdaterPtr _profModelUpdater;
        ProfileStrs formProfileStrs(const std::string &name, const TrainProfile &profile);
    public:
        explicit SettingsController(
                const ISettWinPtr &settingsWin,
                const ITrainProfMEditPtr &trainProfModel,
                const IProfMUpdaterPtr &profModelUpdater
        );

    private:
        void onPositionChanged(int index, const std::string &oldName, const ProfileStrs &profileStrs, const std::string &newName) override;

    public:
        void onSaveBtnClicked() override;

    public:

        void show() override;
    };
}
