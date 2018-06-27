#pragma once

#include <TrainProfiles/TrainProfile.h>
#include <memory>

namespace breathe_trainer{
    class ISettings {
    public:
        virtual void save(const ProfileNameList &list, const ProfileMap &map) = 0;
        virtual ProfileWithNameVect load() = 0;
    };
    typedef std::shared_ptr<ISettings> ISettingsPtr;
}
