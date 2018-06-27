#pragma once

#include <map>
#include "ITrainProfilesModelCopy.h"
#include "ITrainProfilesModelEdit.h"

namespace breathe_trainer {
    class TrainProfilesModel: public ITrainProfilesModelCopy, public ITrainProfilesModelEdit {
    private:
        ProfileMap _profiles;
        ProfileNameList _profileNames;
    public:
        ProfileNameList::const_iterator profileNamesBegin() override;
        ProfileNameList::const_iterator profileNamesEnd() override;

        TrainProfile getProfileByName(const std::string &name) override;

        ProfileMap &profileMap() override;

        ProfileNameList &profileList() override;

        explicit TrainProfilesModel(const ProfileWithNameVect &profiles);

        bool setProfile(const std::string &str, const TrainProfile &prof, const std::string &oldStr) override;

        bool addProfile(const std::string &name) override;

        void deleteProfile(const std::string &str) override;

        void copyModel(const ITrainProfMCopyPtr &other) override;

        bool moveDown(const std::string &str) override;

        bool moveUp(const std::string &str) override;

        uint_fast32_t numProfiles() override;

        void init(const ProfileWithNameVect &profiles) override;
    };
}
