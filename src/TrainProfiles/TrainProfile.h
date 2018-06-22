#pragma once

#include <TrainerCommon.h>
#include <list>
#include <map>

namespace breathe_trainer {
    struct TrainProfile {
        TimeSec inhalationTime;
        TimeSec pauseTimeAfterInhalation;
        TimeSec exhalationTime;
        TimeSec pauseTimeAfterExhalation;
    };

    typedef std::list<std::string> ProfileNameList;
    typedef std::map<std::string, TrainProfile> ProfileMap;
}
