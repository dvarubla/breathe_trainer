#pragma once

#include <string>
#include <vector>
#include <memory>
#include "TrainProfile.h"

namespace breathe_trainer {
    class ITrainProfilesModel {
    public:
        virtual ProfileNameList::const_iterator profileNamesBegin() = 0;
        virtual ProfileNameList::const_iterator profileNamesEnd() = 0;
        virtual TrainProfile getProfileByName(const std::string &name) = 0;
        virtual uint_fast32_t numProfiles() = 0;
    };

    typedef std::shared_ptr<ITrainProfilesModel> ITrainProfMPtr;
}
