#pragma once

#include <TrainProfiles/TrainProfile.h>
#include <memory>
#include "WidthHeight.h"

namespace breathe_trainer{
    class ISettings {
    public:
        virtual void saveProfiles(const ProfileNameList &list, const ProfileMap &map) = 0;
        virtual ProfileWithNameVect loadProfiles() = 0;
        virtual void saveWindowData(const WHMap &map) = 0;
        virtual WHMap loadWindowData() = 0;
    };
    typedef std::shared_ptr<ISettings> ISettingsPtr;
}
