#pragma once

#include <TrainProfiles/ITrainProfilesModel.h>
#include <TrainProfiles/IProfileModelsUpdater.h>
#include <Settings/IWindowSettingsModel.h>
#include "ISettingsWindow.h"
#include "ISettingsController.h"

namespace breathe_trainer {
    class SettingsController: public ISettingsController {
    private:
        ISettWinPtr _settingsWin;
        ITrainProfMEditPtr _trainProfModel;
        IProfMUpdaterPtr _profModelUpdater;
        IWinSettMPtr _winSettModel;
        ProfileData formProfileData(const std::string &name, const TrainProfile &profile);
        bool saveCurrent(int index, const std::string &name, const ProfileData &profileData);
        void initWindow();
        void setUpDownButtons();
    public:
        explicit SettingsController(
                const ISettWinPtr &settingsWin,
                const ITrainProfMEditPtr &trainProfModel,
                const IProfMUpdaterPtr &profModelUpdater,
                const IWinSettMPtr &winSettModel
        );
        void onPositionChanged(int index, const std::string &oldName, const ProfileData &profileData, const std::string &newName) override;
        void onSaveBtnClicked() override;

        void onCancelBtnClicked() override;

        void onMoveUpBtnClicked() override;

        void onMoveDownBtnClicked() override;

        void onAddBtnClicked() override;

        void onDeleteBtnClicked() override;

        void onResize(uint_fast32_t w, uint_fast32_t h) override;

        void onCommit() override;

    public:
        void show() override;
    };
}
