#pragma once

#include <map>
#include "ITrainProfilesModelCopy.h"
#include "ITrainProfilesModelEdit.h"

namespace breathe_trainer {
    class TrainProfilesModel: public ITrainProfilesModelCopy, public ITrainProfilesModelEdit {
    private:
        std::map<std::string, TrainProfile> _profiles;
        ProfileNameList _profileNames;
    public:
        ProfileNameList::const_iterator profileNamesBegin() override;
        ProfileNameList::const_iterator profileNamesEnd() override;

        TrainProfile getProfileByName(const std::string &name) override;

        ProfileMap &profileMap() override;

        ProfileNameList &profileList() override;

        explicit TrainProfilesModel(const std::vector<ProfileWithName> &profiles);

        void setProfile(const std::string &str, const TrainProfile &prof) override;
    };
}
