#pragma once

#include <TrainProfiles/ITrainProfilesModel.h>
#include "ITrainerModel.h"
#include "ITrainerWindow.h"
#include "ITrainerController.h"
#include <SettingsWindow/ISettingsController.h>
#include <Settings/IWindowSettingsModel.h>
#include <TrainProfiles/ISettingsRestorer.h>

namespace breathe_trainer {
    class TrainerController: public ITrainerController {
    private:
        ITrainMPtr _trainModel;
        ITrainProfMPtr _trainProfModel;
        ITrainWinPtr _window;
        ISettCtrlPtr _settingsCtrl;
        IWinSettMPtr _winSettModel;
        ISettRestorerPtr _restorer;
        const static uint_fast8_t NUM_INHALE_COLORS = 3;
        std::array<uint_fast32_t, NUM_INHALE_COLORS> inhaleColors = {0x00FF00, 0xF0F000, 0xFF0000};
        void clearWindow();
        void updateProfiles();
    public:
        void onStateChanged() override;

        TrainerController(
                const ITrainMPtr &trainModel,
                const ITrainWinPtr &window,
                const ITrainProfMPtr &trainProfModel,
                const ISettCtrlPtr &settingsCtrl,
                const IWinSettMPtr &winSettModel,
                const ISettRestorerPtr &restorer
        );

        void onProgressChanged() override;

        void onStartPressed() override;

        void onStopPressed() override;

        void onEditPressed() override;

        void onCommit() override;

        void onResize(uint_fast32_t w, uint_fast32_t h) override;

        void onRestoreActClicked() override;

    public:

        void init();
    };
}
