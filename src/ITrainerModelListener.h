#pragma once

#include <memory>

namespace breathe_trainer {
    class ITrainerModelListener {
    public:
        virtual void onStateChanged() = 0;
        virtual void onProgressChanged() = 0;
    };

    typedef std::shared_ptr<ITrainerModelListener> ITMListenerPtr;
    typedef std::weak_ptr<ITrainerModelListener> ITMListenerWPtr;
}
