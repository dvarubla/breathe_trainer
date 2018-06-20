#pragma once

#include <map>
#include "ITrainProfilesModel.h"

namespace breathe_trainer {
    class TrainProfilesModel: public virtual ITrainProfilesModel {
    private:
        std::map<std::string, TrainProfile> _profiles;
        ProfileNameList _profileNames;
    public:
        ProfileNameList::const_iterator profileNamesBegin();
        ProfileNameList::const_iterator profileNamesEnd();

        TrainProfile getProfileByName(const std::string &name) override;

        explicit TrainProfilesModel(const std::vector<ProfileWithName> &profiles);
    };
}
