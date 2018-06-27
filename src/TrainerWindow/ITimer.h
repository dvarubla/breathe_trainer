#pragma once

#include "ITimerListener.h"

namespace breathe_trainer {
    class ITimer {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void setStop() = 0;
        virtual bool isWorking() = 0;
    };

    typedef std::shared_ptr<ITimer> ITimerPtr;
}
