#pragma once

namespace breathe_trainer {
    class ITrainerWindowListener {
    public:
        virtual void onStartPressed() = 0;
        virtual void onStopPressed() = 0;
        virtual void onEditPressed() = 0;
        virtual void onResize(uint_fast32_t w, uint_fast32_t h) = 0;
    };
    typedef std::shared_ptr<ITrainerWindowListener> ITrainWinListPtr;
    typedef std::weak_ptr<ITrainerWindowListener> ITrainWinListWPtr;
}
