#pragma once

#include "TrainerCommon.h"
#include "ITrainerModelListener.h"
#include "ITimerListener.h"
#include <TrainProfiles/TrainProfile.h>

namespace breathe_trainer {
    enum class Phase{
        INHALATION,
        PAUSE,
        EXHALATION
    };
    class ITrainerModel: public ITimerListener {
    public:
        virtual bool isStarted() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual TimeStr getTotalTime() = 0;
        virtual Phase getPhase() = 0;
        virtual TimeStr getPhaseTime() = 0;
        virtual double getAmount() = 0;
        virtual void setModelListener(const ITrainMListWPtr &ptr) = 0;
        virtual void setProfile(const TrainProfile &profile) = 0;
        virtual uint_fast32_t getCycleNum() = 0;
    };

    typedef std::shared_ptr<ITrainerModel> ITrainMPtr;
}

