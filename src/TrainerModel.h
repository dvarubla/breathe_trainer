#pragma once

#include <thread>
#include <atomic>
#include "ITrainerModel.h"
#include "TrainProfile.h"

namespace breathe_trainer {
    class TrainerModel: public ITrainerModel{
    private:
        enum class InternalPhase{
            INHALATION,
            PAUSE_AFTER_INHALATION,
            EXHALATION,
            PAUSE_AFTER_EXHALATION
        };
        const TimeSec THREAD_INTERVAL_MS = 100;
        const uint_fast8_t STR_PART_LEN = 2;
        ITMListenerWPtr _listenerPtr;
        TrainProfile _profile;

        std::chrono::system_clock::time_point _startTime;
        std::chrono::seconds _timeElapsedSec;
        std::chrono::system_clock::time_point _startPhaseTime;
        InternalPhase _curPhase;

        std::chrono::milliseconds _curPhaseMS;
        std::chrono::seconds _curPhaseCurSec;
        std::chrono::seconds _curPhaseTotalSec;

        std::thread _timerThread;
        bool _threadStarted;
        std::atomic_bool _threadWorking;

        void thread_func();
        template<class DurationIn, class FirstDuration, class...RestDurations>
        std::string formatDuration(DurationIn d);
        void processTimerTick();
        void notifyListenerState();
        void setPhase();
    public:
        explicit TrainerModel(const TrainProfile &profile);
        ~TrainerModel();
        void start() override;
        void stop() override;

        TimeStr getTotalTime() override;

        Phase getPhase() override;

        TimeStr getPhaseTime() override;

        double getAmount() override;

        void setModelListener(const ITMListenerWPtr &ptr) override;
    };
}
