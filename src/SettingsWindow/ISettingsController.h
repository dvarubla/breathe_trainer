#pragma once

#include "ISettingsWindowListener.h"

namespace breathe_trainer{
    class ISettingsController: public ISettingsWindowListener, public IProfileModelUpdaterListener{
    public:
        virtual void show() = 0;
    };

    typedef std::shared_ptr<ISettingsController> ISettCtrlPtr;
}
