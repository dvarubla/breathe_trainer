#pragma once

#include <thread>
#include <atomic>
#include "ITrainerModel.h"
#include "ITimer.h"

namespace breathe_trainer {
    class TrainerModel: public ITrainerModel{
    private:
        enum class InternalPhase{
            INHALATION,
            PAUSE_AFTER_INHALATION,
            EXHALATION,
            PAUSE_AFTER_EXHALATION
        };
        const uint_fast8_t STR_PART_LEN = 2;

        const ITimerPtr _timer;
        const TimeSec _timerProgressInterval;

        ITrainMListWPtr _listenerPtr;
        TrainProfile _profile;

        TimeSec _elapsedSec;
        InternalPhase _curPhase;

        TimeMSec _curPhaseMS;
        TimeSec _curPhaseCurSec;
        TimeSec _curPhaseTotalSec;

        uint_fast32_t _cycleNum;

        template<class DurationIn, class FirstDuration, class...RestDurations>
        std::string formatDuration(DurationIn d);
        void notifyListenerState();
        void setPhase();
    public:
        explicit TrainerModel(const ITimerPtr &timer, TimeMSec timerProgressInterval);

        void setProfile(const TrainProfile &profile) override;

        void start() override;
        void stop() override;
        bool isStarted() override;

        TimeStr getTotalTime() override;

        Phase getPhase() override;

        TimeStr getPhaseTime() override;

        double getAmount() override;

        void setModelListener(const ITrainMListWPtr &ptr) override;

        void onSecondPassed() override;

        void onProgress() override;

        void onStart() override;

        uint_fast32_t getCycleNum() override;
    };
}
