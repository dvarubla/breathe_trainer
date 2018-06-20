#pragma once

#include <TrainProfiles/ITrainProfilesModel.h>
#include "ITrainerModel.h"
#include "ITrainerWindow.h"
#include "ITrainerController.h"

namespace breathe_trainer {
    class TrainerController: public ITrainerController {
    private:
        ITrainMPtr _trainModel;
        ITrainProfMPtr _trainProfModel;
        ITrainWinPtr _window;
        const static uint_fast8_t NUM_INHALE_COLORS = 3;
        std::array<uint_fast32_t, NUM_INHALE_COLORS> inhaleColors = {0x00FF00, 0xF0F000, 0xFF0000};
        void clearWindow();
    public:
        void onStateChanged() override;

        TrainerController(const ITrainMPtr &trainModel, const ITrainWinPtr &window, const ITrainProfMPtr &trainProfModel);

        void onProgressChanged() override;

        void onStartPressed() override;

        void onStopPressed() override;

    public:

        void init();
    };
}
