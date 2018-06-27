#pragma once

#include <memory>

namespace breathe_trainer{
    class ISettingsListener {
    public:
        virtual void onAppExit() = 0;
    };

    typedef std::weak_ptr<ISettingsListener> ISettListWPtr;
}
