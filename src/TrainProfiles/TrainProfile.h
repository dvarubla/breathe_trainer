#pragma once

#include "TrainerCommon.h"

namespace breathe_trainer {
    struct TrainProfile {
        TimeSec inhalationTime;
        TimeSec pauseTimeAfterInhalation;
        TimeSec exhalationTime;
        TimeSec pauseTimeAfterExhalation;
    };
}
