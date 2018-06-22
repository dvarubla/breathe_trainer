#pragma once

#include <memory>
#include <TrainerCommon.h>

namespace breathe_trainer {
    class ISettingsWindow {
    public:
        virtual void showWindow() = 0;
        virtual void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) = 0;
    };
    typedef std::shared_ptr<ISettingsWindow> ISettWinPtr;
}
