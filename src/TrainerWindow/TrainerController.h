#pragma once

#include "ITrainerModel.h"
#include "ITrainerWindow.h"
#include "ITrainerController.h"

namespace breathe_trainer {
    class TrainerController: public ITrainerController {
    private:
        ITMPtr _model;
        ITWPtr _window;
        const static uint_fast8_t NUM_INHALE_COLORS = 3;
        std::array<uint_fast32_t, NUM_INHALE_COLORS> inhaleColors = {0x00FF00, 0xF0F000, 0xFF0000};
    public:
        void onStateChanged() override;

        TrainerController(const ITMPtr &model, const ITWPtr &window);

        void onProgressChanged() override;

        void init();
    };
}
