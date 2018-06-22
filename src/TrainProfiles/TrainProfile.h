#pragma once

#include <TrainerCommon.h>
#include <list>
#include <map>
#include <unordered_map>

namespace breathe_trainer {
    struct TrainProfile {
        TimeSec inhalationTime;
        TimeSec pauseTimeAfterInhalation;
        TimeSec exhalationTime;
        TimeSec pauseTimeAfterExhalation;
    };
    typedef std::list<std::string> ProfileNameList;
    struct ProfileMapItem{
        ProfileNameList::iterator it;
        TrainProfile profile;
    };
    typedef std::unordered_map<std::string, ProfileMapItem> ProfileMap;
}
