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
        void saveCurrent(int index, const std::string &name, const ProfileStrs &profileStrs);
        void initWindow();
    public:
        explicit SettingsController(
                const ISettWinPtr &settingsWin,
                const ITrainProfMEditPtr &trainProfModel,
                const IProfMUpdaterPtr &profModelUpdater
        );
        void onPositionChanged(int index, const std::string &oldName, const ProfileStrs &profileStrs, const std::string &newName) override;
        void onSaveBtnClicked() override;

        void onCancelBtnClicked() override;

        void onMoveUpBtnClicked() override;

        void onMoveDownBtnClicked() override;

        void onAddBtnClicked() override;

    public:
        void show() override;
    };
}
