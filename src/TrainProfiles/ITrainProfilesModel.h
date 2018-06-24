#pragma once

#include <string>
#include <vector>
#include <memory>
#include "TrainProfile.h"

namespace breathe_trainer {
    class ITrainProfilesModel {
    public:
        struct ProfileWithName {
            TrainProfile profile;
            std::string name;
        };
        virtual ProfileNameList::const_iterator profileNamesBegin() = 0;
        virtual ProfileNameList::const_iterator profileNamesEnd() = 0;
        virtual bool moveDown(const std::string &str) = 0;
        virtual bool moveUp(const std::string &str) = 0;
        virtual TrainProfile getProfileByName(const std::string &name) = 0;
    };

    typedef std::shared_ptr<ITrainProfilesModel> ITrainProfMPtr;
}
