#pragma once

#include <memory>

namespace breathe_trainer{
    class ISettingsRestorer {
    public:
        virtual void restoreDefaults() = 0;
    };

    typedef std::shared_ptr<ISettingsRestorer> ISettRestorerPtr;
}
