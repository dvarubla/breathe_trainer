#pragma once

#include <TrainerCommon.h>
#include <thread>
#include <atomic>
#include "ITimer.h"

namespace breathe_trainer {
    class Timer : public ITimer{
    private:
        ITimerListWPtr _timerListener;
        std::chrono::milliseconds _secondInterval;
        std::chrono::milliseconds _progressInterval;
        std::thread _timerThread;
        bool _threadStarted;
        std::atomic_bool _threadWorking;
        std::chrono::system_clock::time_point _startTime;
        std::chrono::milliseconds _timeElapsedMSecForSeconds;
        std::chrono::milliseconds _timeElapsedMSecForProgress;
        void threadFunc();
    public:
        Timer(TimeMSec secondInterval, TimeMSec progressInterval);
        ~Timer();
        void setListener(const ITimerListWPtr &timerListener);
        void start() override;
        void stop() override;
        bool isWorking() override;
    };
}
