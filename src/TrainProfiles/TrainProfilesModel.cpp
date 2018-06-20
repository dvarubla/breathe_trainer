#include <algorithm>
#include "TrainProfilesModel.h"

namespace breathe_trainer{

    TrainProfile TrainProfilesModel::getProfileByName(const std::string &str) {
        return _profiles[str];
    }

    TrainProfilesModel::TrainProfilesModel(const std::vector<TrainProfilesModel::ProfileWithName> &profiles) {
        std::transform(profiles.begin(), profiles.end(), std::back_inserter(_profileNames), [this](auto i){
            _profiles.insert(std::make_pair<>(i.name, i.profile));
            return i.name;
        });
    }

    ProfileNameList::const_iterator TrainProfilesModel::profileNamesBegin() {
        return _profileNames.cbegin();
    }

    ProfileNameList::const_iterator TrainProfilesModel::profileNamesEnd() {
        return _profileNames.cend();
    }
}