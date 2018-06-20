#pragma once

namespace breathe_trainer {
    class ITrainerWindowListener {
    public:
        virtual void onStartPressed() = 0;
        virtual void onStopPressed() = 0;
    };
    typedef std::shared_ptr<ITrainerWindowListener> ITWinListenerPtr;
    typedef std::weak_ptr<ITrainerWindowListener> ITWinListenerWPtr;
}
