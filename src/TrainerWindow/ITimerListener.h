#pragma once

#include <memory>

namespace breathe_trainer {
    class ITimerListener {
    public:
        virtual void onSecondPassed() = 0;
        virtual void onProgress() = 0;
        virtual void onStart() = 0;
    };

    typedef std::weak_ptr<ITimerListener> ITimerListWPtr;
}
