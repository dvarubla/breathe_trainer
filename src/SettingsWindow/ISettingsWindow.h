#pragma once

#include <memory>
#include <TrainProfiles/TrainProfile.h>

namespace breathe_trainer {
    struct ProfileStrs{
        std::string inhalationTime;
        std::string pauseTimeAfterInhalation;
        std::string exhalationTime;
        std::string pauseTimeAfterExhalation;
    };
    class ISettingsWindow {
    public:
        virtual void showWindow() = 0;
        virtual void addProfiles(ProfileNameList::const_iterator begin, ProfileNameList::const_iterator end) = 0;
        virtual void setFieldStrings(const ProfileStrs &strs) = 0;
    };
    typedef std::shared_ptr<ISettingsWindow> ISettWinPtr;
}
