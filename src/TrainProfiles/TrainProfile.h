#pragma once

#include <TrainerCommon.h>
#include <list>
#include <map>
#include <unordered_map>

namespace breathe_trainer {
    struct TrainProfileTimeItem{
        TimeSec initial;
        Cycle startCycle;
        Cycle everyCycle;
        TimeSec delta;
    };
    struct TrainProfile {
        TrainProfileTimeItem inhalationTime;
        TrainProfileTimeItem pauseTimeAfterInhalation;
        TrainProfileTimeItem exhalationTime;
        TrainProfileTimeItem pauseTimeAfterExhalation;
        Cycle restStart;
        Cycle restDur;
        TimeSec restInhalationTime;
        TimeSec restPauseTimeAfterInhalation;
        TimeSec restExhalationTime;
        TimeSec restPauseTimeAfterExhalation;
    };
    typedef std::list<std::string> ProfileNameList;
    struct ProfileMapItem{
        ProfileNameList::iterator it;
        TrainProfile profile;
    };
    typedef std::unordered_map<std::string, ProfileMapItem> ProfileMap;
}
