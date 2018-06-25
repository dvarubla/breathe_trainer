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
        ProfileData formProfileData(const std::string &name, const TrainProfile &profile);
        bool saveCurrent(int index, const std::string &name, const ProfileData &profileData);
        void initWindow();
        void setUpDownButtons();
    public:
        explicit SettingsController(
                const ISettWinPtr &settingsWin,
                const ITrainProfMEditPtr &trainProfModel,
                const IProfMUpdaterPtr &profModelUpdater
        );
        void onPositionChanged(int index, const std::string &oldName, const ProfileData &profileData, const std::string &newName) override;
        void onSaveBtnClicked() override;

        void onCancelBtnClicked() override;

        void onMoveUpBtnClicked() override;

        void onMoveDownBtnClicked() override;

        void onAddBtnClicked() override;

        void onDeleteBtnClicked() override;

    public:
        void show() override;
    };
}
